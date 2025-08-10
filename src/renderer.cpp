#include "renderer.hpp"
#include "shader_utils.hpp"
#include <iostream>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

Renderer::Renderer()
    : window_(nullptr)
    , width_(WINDOW_WIDTH)
    , height_(WINDOW_HEIGHT)
    , viewId_(0) {
    
    // Initialize bgfx handles to invalid
    backgroundProgram_ = BGFX_INVALID_HANDLE;
    spriteProgram_ = BGFX_INVALID_HANDLE;
    textProgram_ = BGFX_INVALID_HANDLE;
    backgroundVB_ = BGFX_INVALID_HANDLE;
    backgroundIB_ = BGFX_INVALID_HANDLE;
    spriteVB_ = BGFX_INVALID_HANDLE;
    spriteIB_ = BGFX_INVALID_HANDLE;
    timeUniform_ = BGFX_INVALID_HANDLE;
    colorUniform_ = BGFX_INVALID_HANDLE;
    transformUniform_ = BGFX_INVALID_HANDLE;
}

Renderer::~Renderer() {
    Shutdown();
}

bool Renderer::Initialize(GLFWwindow* window, int width, int height) {
    window_ = window;
    width_ = width;
    height_ = height;
    
    // Initialize bgfx
    bgfx::Init init;
    init.type = bgfx::RendererType::OpenGL;
    init.resolution.width = width_;
    init.resolution.height = height_;
    init.resolution.reset = BGFX_RESET_VSYNC;
    
    if (!bgfx::init(init)) {
        std::cerr << "Failed to initialize bgfx" << std::endl;
        return false;
    }
    
    // Set view 0 clear state
    bgfx::setViewClear(viewId_, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000FF, 1.0f, 0);
    bgfx::setViewRect(viewId_, 0, 0, width_, height_);
    
    // Create uniforms
    timeUniform_ = bgfx::createUniform("u_time", bgfx::UniformType::Vec4);
    colorUniform_ = bgfx::createUniform("u_color", bgfx::UniformType::Vec4);
    transformUniform_ = bgfx::createUniform("u_transform", bgfx::UniformType::Mat4);
    
    // Load shaders
    if (!LoadShaders()) {
        std::cerr << "Failed to load shaders" << std::endl;
        return false;
    }
    
    // Create vertex buffers
    if (!CreateBackgroundBuffers()) {
        std::cerr << "Failed to create background buffers" << std::endl;
        return false;
    }
    
    if (!CreateSpriteBuffers()) {
        std::cerr << "Failed to create sprite buffers" << std::endl;
        return false;
    }
    
    return true;
}

void Renderer::Shutdown() {
    // Destroy bgfx resources
    if (bgfx::isValid(backgroundProgram_)) bgfx::destroy(backgroundProgram_);
    if (bgfx::isValid(spriteProgram_)) bgfx::destroy(spriteProgram_);
    if (bgfx::isValid(textProgram_)) bgfx::destroy(textProgram_);
    if (bgfx::isValid(backgroundVB_)) bgfx::destroy(backgroundVB_);
    if (bgfx::isValid(backgroundIB_)) bgfx::destroy(backgroundIB_);
    if (bgfx::isValid(spriteVB_)) bgfx::destroy(spriteVB_);
    if (bgfx::isValid(spriteIB_)) bgfx::destroy(spriteIB_);
    if (bgfx::isValid(timeUniform_)) bgfx::destroy(timeUniform_);
    if (bgfx::isValid(colorUniform_)) bgfx::destroy(colorUniform_);
    if (bgfx::isValid(transformUniform_)) bgfx::destroy(transformUniform_);
    
    bgfx::shutdown();
}

void Renderer::BeginFrame() {
    bgfx::setViewClear(viewId_, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000FF, 1.0f, 0);
    bgfx::setViewRect(viewId_, 0, 0, width_, height_);
}

void Renderer::EndFrame() {
    bgfx::frame();
}

void Renderer::RenderBackground(float time) {
    if (!bgfx::isValid(backgroundProgram_)) return;
    
    // Set shader program
    bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_ALWAYS);
    bgfx::setProgram(backgroundProgram_);
    
    // Set time uniform
    float timeData[4] = { time, 0.0f, 0.0f, 0.0f };
    bgfx::setUniform(timeUniform_, timeData);
    
    // Set vertex buffer
    bgfx::setVertexBuffer(0, backgroundVB_);
    bgfx::setIndexBuffer(backgroundIB_);
    
    // Submit
    bgfx::submit(viewId_);
}

void Renderer::RenderSprite(const glm::vec2& position, float rotation, float scale, uint32_t color) {
    if (!bgfx::isValid(spriteProgram_)) return;
    
    // Set shader program
    bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_ALWAYS | BGFX_STATE_BLEND_ALPHA);
    bgfx::setProgram(spriteProgram_);
    
    // Create transform matrix
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(position.x, position.y, 0.0f));
    transform = glm::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(scale, scale, 1.0f));
    
    // Set transform uniform
    bgfx::setUniform(transformUniform_, glm::value_ptr(transform));
    
    // Set color uniform
    float r = ((color >> 24) & 0xFF) / 255.0f;
    float g = ((color >> 16) & 0xFF) / 255.0f;
    float b = ((color >> 8) & 0xFF) / 255.0f;
    float a = (color & 0xFF) / 255.0f;
    float colorData[4] = { r, g, b, a };
    bgfx::setUniform(colorUniform_, colorData);
    
    // Set vertex buffer
    bgfx::setVertexBuffer(0, spriteVB_);
    bgfx::setIndexBuffer(spriteIB_);
    
    // Submit
    bgfx::submit(viewId_);
}

void Renderer::RenderText(const std::string& text, const glm::vec2& position, float scale, uint32_t color) {
    // For now, just render as a colored rectangle
    // In a full implementation, this would use a font texture atlas
    RenderSprite(position, 0.0f, scale, color);
}

void Renderer::RenderUI() {
    // UI rendering would go here
    // For now, just clear the view
}

bool Renderer::LoadShaders() {
    // Load background shaders
    backgroundProgram_ = ShaderUtils::CreateProgram("background.vert", "background.frag");
    if (!bgfx::isValid(backgroundProgram_)) {
        return false;
    }
    
    // Load sprite shaders
    spriteProgram_ = ShaderUtils::CreateProgram("sprite.vert", "sprite.frag");
    if (!bgfx::isValid(spriteProgram_)) {
        return false;
    }
    
    // For now, use sprite program for text
    textProgram_ = spriteProgram_;
    
    return true;
}

bool Renderer::CreateBackgroundBuffers() {
    // Create full-screen quad for background
    struct Vertex {
        float x, y;
        float u, v;
    };
    
    Vertex vertices[] = {
        { -1.0f, -1.0f, 0.0f, 1.0f },
        {  1.0f, -1.0f, 1.0f, 1.0f },
        {  1.0f,  1.0f, 1.0f, 0.0f },
        { -1.0f,  1.0f, 0.0f, 0.0f }
    };
    
    uint16_t indices[] = {
        0, 1, 2,
        0, 2, 3
    };
    
    // Create vertex buffer
    backgroundVB_ = bgfx::createVertexBuffer(
        bgfx::copy(vertices, sizeof(vertices)),
        backgroundLayout_
    );
    
    // Create index buffer
    backgroundIB_ = bgfx::createIndexBuffer(
        bgfx::copy(indices, sizeof(indices))
    );
    
    // Setup vertex layout
    backgroundLayout_.begin()
        .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .end();
    
    return bgfx::isValid(backgroundVB_) && bgfx::isValid(backgroundIB_);
}

bool Renderer::CreateSpriteBuffers() {
    // Create sprite quad
    struct Vertex {
        float x, y;
        float u, v;
    };
    
    Vertex vertices[] = {
        { -0.5f, -0.5f, 0.0f, 1.0f },
        {  0.5f, -0.5f, 1.0f, 1.0f },
        {  0.5f,  0.5f, 1.0f, 0.0f },
        { -0.5f,  0.5f, 0.0f, 0.0f }
    };
    
    uint16_t indices[] = {
        0, 1, 2,
        0, 2, 3
    };
    
    // Create vertex buffer
    spriteVB_ = bgfx::createVertexBuffer(
        bgfx::copy(vertices, sizeof(vertices)),
        spriteLayout_
    );
    
    // Create index buffer
    spriteIB_ = bgfx::createIndexBuffer(
        bgfx::copy(indices, sizeof(indices))
    );
    
    // Setup vertex layout
    spriteLayout_.begin()
        .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .end();
    
    return bgfx::isValid(spriteVB_) && bgfx::isValid(spriteIB_);
}

void Renderer::SetBackgroundShader(float time) {
    // This is handled in RenderBackground
}

void Renderer::SetSpriteShader() {
    // This is handled in RenderSprite
}