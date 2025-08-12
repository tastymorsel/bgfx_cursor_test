#include "renderer.hpp"
#include "shader_utils.hpp"
#include <iostream>
#include <bgfx/bgfx.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer()
    : window_(nullptr)
    , width_(WINDOW_WIDTH)
    , height_(WINDOW_HEIGHT)
    , viewId_(0) {
    
    // Initialize bgfx handles to invalid
    backgroundProgram_ = {bgfx::BGFX_INVALID_HANDLE};
    spriteProgram_ = {bgfx::BGFX_INVALID_HANDLE};
    textProgram_ = {bgfx::BGFX_INVALID_HANDLE};
    backgroundVB_ = {bgfx::BGFX_INVALID_HANDLE};
    backgroundIB_ = {bgfx::BGFX_INVALID_HANDLE};
    spriteVB_ = {bgfx::BGFX_INVALID_HANDLE};
    spriteIB_ = {bgfx::BGFX_INVALID_HANDLE};
    timeUniform_ = {bgfx::BGFX_INVALID_HANDLE};
    colorUniform_ = {bgfx::BGFX_INVALID_HANDLE};
    transformUniform_ = {bgfx::BGFX_INVALID_HANDLE};
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
    init.resolution.reset = bgfx::BGFX_RESET_VSYNC;
    
    if (!bgfx::init(init)) {
        std::cerr << "Failed to initialize bgfx" << std::endl;
        return false;
    }
    
    // Set view 0 clear state
    bgfx::setViewClear(viewId_, bgfx::BGFX_CLEAR_COLOR | bgfx::BGFX_CLEAR_DEPTH, 0x000000FF, 1.0f, 0);
    bgfx::setViewRect(viewId_, 0, 0, width_, height_);
    
    // Create uniforms
    timeUniform_ = bgfx::createUniform("u_time", bgfx::UniformType::Vec4);
    colorUniform_ = bgfx::createUniform("u_color", bgfx::UniformType::Vec4);
    transformUniform_ = bgfx::createUniform("u_transform", bgfx::UniformType::Mat4);
    
    // Create vertex buffers
    if (!CreateBackgroundBuffers()) {
        std::cerr << "Failed to create background buffers" << std::endl;
        return false;
    }
    
    if (!CreateSpriteBuffers()) {
        std::cerr << "Failed to create sprite buffers" << std::endl;
        return false;
    }
    
    // Load shaders
    if (!LoadShaders()) {
        std::cerr << "Failed to load shaders" << std::endl;
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
    bgfx::setViewClear(viewId_, bgfx::BGFX_CLEAR_COLOR | bgfx::BGFX_CLEAR_DEPTH, 0x000000FF, 1.0f, 0);
    bgfx::setViewRect(viewId_, 0, 0, width_, height_);
}

void Renderer::EndFrame() {
    bgfx::frame();
}

void Renderer::RenderBackground(float time) {
    std::cout << "RenderBackground called with time: " << time << std::endl;
    
    if (!bgfx::isValid(backgroundProgram_)) {
        std::cerr << "Background program is invalid!" << std::endl;
        return;
    }
    
    std::cout << "Rendering background with valid program" << std::endl;
    
    // Set shader program
    bgfx::setState(bgfx::BGFX_STATE_WRITE_RGB | bgfx::BGFX_STATE_WRITE_A | bgfx::BGFX_STATE_DEPTH_TEST_ALWAYS);
    bgfx::setProgram(backgroundProgram_);
    
    // Set time uniform
    float timeData[4] = { time, 0.0f, 0.0f, 0.0f };
    bgfx::setUniform(timeUniform_, timeData);
    
    // Set vertex buffer
    bgfx::setVertexBuffer(0, backgroundVB_);
    bgfx::setIndexBuffer(backgroundIB_);
    
    // Submit
    bgfx::submit(viewId_);
    
    std::cout << "Background render submitted" << std::endl;
}

void Renderer::RenderSprite(const glm::vec2& position, float rotation, float scale, uint32_t color) {
    if (!bgfx::isValid(spriteProgram_)) return;
    
    // Set shader program
    bgfx::setState(bgfx::BGFX_STATE_WRITE_RGB | bgfx::BGFX_STATE_WRITE_A | bgfx::BGFX_STATE_DEPTH_TEST_ALWAYS | bgfx::BGFX_STATE_BLEND_ALPHA);
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
    std::cout << "LoadShaders called" << std::endl;
    
    // Load background shaders
    std::cout << "Loading background shaders..." << std::endl;
    backgroundProgram_ = ShaderUtils::CreateProgram("background.vert", "background.frag");
    if (!bgfx::isValid(backgroundProgram_)) {
        std::cerr << "Failed to create background program" << std::endl;
        return false;
    }
    std::cout << "Background program created successfully" << std::endl;
    
    // Load sprite shaders
    std::cout << "Loading sprite shaders..." << std::endl;
    spriteProgram_ = ShaderUtils::CreateProgram("sprite.vert", "sprite.frag");
    if (!bgfx::isValid(spriteProgram_)) {
        std::cerr << "Failed to create sprite program" << std::endl;
        return false;
    }
    std::cout << "Sprite program created successfully" << std::endl;
    
    // For now, use sprite program for text
    textProgram_ = spriteProgram_;
    
    std::cout << "All shaders loaded successfully" << std::endl;
    return true;
}

bool Renderer::CreateBackgroundBuffers() {
    std::cout << "CreateBackgroundBuffers called" << std::endl;
    
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
    
    // Setup vertex layout first
    backgroundLayout_.begin()
        .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .end();
    
    std::cout << "Creating background vertex buffer..." << std::endl;
    
    // Create vertex buffer
    backgroundVB_ = bgfx::createVertexBuffer(
        bgfx::copy(vertices, sizeof(vertices)),
        backgroundLayout_
    );
    
    std::cout << "Creating background index buffer..." << std::endl;
    
    // Create index buffer
    backgroundIB_ = bgfx::createIndexBuffer(
        bgfx::copy(indices, sizeof(indices))
    );
    
    bool success = bgfx::isValid(backgroundVB_) && bgfx::isValid(backgroundIB_);
    std::cout << "Background buffers created successfully: " << (success ? "yes" : "no") << std::endl;
    
    return success;
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
    
    // Setup vertex layout first
    spriteLayout_.begin()
        .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .end();
    
    // Create vertex buffer
    spriteVB_ = bgfx::createVertexBuffer(
        bgfx::copy(vertices, sizeof(vertices)),
        spriteLayout_
    );
    
    // Create index buffer
    spriteIB_ = bgfx::createIndexBuffer(
        bgfx::copy(indices, sizeof(indices))
    );
    
    return bgfx::isValid(spriteVB_) && bgfx::isValid(spriteIB_);
}

void Renderer::SetBackgroundShader(float time) {
    // This is handled in RenderBackground
}

void Renderer::SetSpriteShader() {
    // This is handled in RenderSprite
}