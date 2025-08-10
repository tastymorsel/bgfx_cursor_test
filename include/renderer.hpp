#pragma once

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <memory>

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    bool Initialize(GLFWwindow* window, int width, int height);
    void Shutdown();
    
    void BeginFrame();
    void EndFrame();
    
    // Rendering functions
    void RenderBackground(float time);
    void RenderSprite(const glm::vec2& position, float rotation, float scale, uint32_t color);
    void RenderText(const std::string& text, const glm::vec2& position, float scale, uint32_t color);
    void RenderUI();
    
    // Shader management
    bool LoadShaders();
    void SetBackgroundShader(float time);
    void SetSpriteShader();
    
    // Getters
    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
    bgfx::ViewId GetViewId() const { return viewId_; }
    
private:
    // Window and rendering context
    GLFWwindow* window_;
    int width_;
    int height_;
    bgfx::ViewId viewId_;
    
    // Shaders and programs
    bgfx::ProgramHandle backgroundProgram_;
    bgfx::ProgramHandle spriteProgram_;
    bgfx::ProgramHandle textProgram_;
    
    // Vertex buffers and layouts
    bgfx::VertexBufferHandle backgroundVB_;
    bgfx::IndexBufferHandle backgroundIB_;
    bgfx::VertexBufferHandle spriteVB_;
    bgfx::IndexBufferHandle spriteIB_;
    
    // Uniforms
    bgfx::UniformHandle timeUniform_;
    bgfx::UniformHandle colorUniform_;
    bgfx::UniformHandle transformUniform_;
    
    // Vertex layouts
    bgfx::VertexLayout backgroundLayout_;
    bgfx::VertexLayout spriteLayout_;
    
    // Shader loading helpers
    bool LoadShader(const std::string& name, bgfx::ShaderHandle& handle);
    bool CreateProgram(const std::string& name, bgfx::ProgramHandle& handle);
    
    // Buffer creation helpers
    bool CreateBackgroundBuffers();
    bool CreateSpriteBuffers();
    
    // Constants
    static constexpr int WINDOW_WIDTH = 1024;
    static constexpr int WINDOW_HEIGHT = 512;
};