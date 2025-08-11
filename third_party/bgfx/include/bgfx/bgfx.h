#pragma once

#include <cstdint>
#include <string>

namespace bgfx {
    // Handle types
    struct ShaderHandle { uint16_t idx; };
    struct ProgramHandle { uint16_t idx; };
    struct VertexBufferHandle { uint16_t idx; };
    struct IndexBufferHandle { uint16_t idx; };
    struct UniformHandle { uint16_t idx; };
    
    // View ID type
    using ViewId = uint8_t;
    
    // Constants
    static const uint16_t BGFX_INVALID_HANDLE = 0xFFFF;
    
    // Uniform types
    enum UniformType {
        Vec4,
        Mat4
    };
    
    // States
    enum State {
        BGFX_STATE_WRITE_RGB = 0x00000001,
        BGFX_STATE_WRITE_A = 0x00000002,
        BGFX_STATE_DEPTH_TEST_ALWAYS = 0x00000004,
        BGFX_STATE_BLEND_ALPHA = 0x00000008
    };
    
    // Clear flags
    enum Clear {
        BGFX_CLEAR_COLOR = 0x00000001,
        BGFX_CLEAR_DEPTH = 0x00000002
    };
    
    // Reset flags
    enum Reset {
        BGFX_RESET_VSYNC = 0x00000001
    };
    
    // Renderer types
    enum RendererType {
        OpenGL
    };
    
    // Vertex attributes
    enum Attrib {
        Position,
        TexCoord0
    };
    
    enum AttribType {
        Float
    };
    
    // Memory structure
    struct Memory {
        const uint8_t* data;
        uint32_t size;
    };
    
    // Init structure
    struct Init {
        RendererType type;
        struct {
            uint32_t width;
            uint32_t height;
            uint32_t reset;
        } resolution;
    };
    
    // Vertex layout
    class VertexLayout {
    public:
        VertexLayout& begin() { return *this; }
        VertexLayout& add(Attrib attrib, uint8_t num, AttribType type) { return *this; }
        VertexLayout& end() { return *this; }
    };
    
    // Functions
    bool init(const Init& init);
    void shutdown();
    void frame();
    void setViewClear(uint8_t viewId, uint16_t flags, uint32_t rgba, float depth, uint8_t stencil);
    void setViewRect(uint8_t viewId, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    void setState(uint64_t state);
    void setProgram(ProgramHandle program);
    void setUniform(UniformHandle uniform, const void* value);
    void setVertexBuffer(uint8_t stream, VertexBufferHandle handle);
    void setIndexBuffer(IndexBufferHandle handle);
    void submit(uint8_t viewId);
    
    // Handle validation
    template<typename T>
    bool isValid(T handle) { return handle.idx != BGFX_INVALID_HANDLE; }
    
    // Shader creation
    ShaderHandle createShader(const Memory* mem);
    ShaderHandle createShader(const std::string& vertexShader, const std::string& fragmentShader);
    
    // Program creation
    ProgramHandle createProgram(ShaderHandle vertexShader, ShaderHandle fragmentShader);
    
    // Buffer creation
    VertexBufferHandle createVertexBuffer(const Memory* mem, const VertexLayout& layout);
    IndexBufferHandle createIndexBuffer(const Memory* mem);
    UniformHandle createUniform(const char* name, UniformType type);
    
    // Handle validation functions
    bool isValid(ShaderHandle handle);
    bool isValid(ProgramHandle handle);
    bool isValid(VertexBufferHandle handle);
    bool isValid(IndexBufferHandle handle);
    bool isValid(UniformHandle handle);
    
    // Cleanup functions
    void destroy(ShaderHandle handle);
    void destroy(ProgramHandle handle);
    void destroy(VertexBufferHandle handle);
    void destroy(IndexBufferHandle handle);
    void destroy(UniformHandle handle);
    
    // Copy functions
    template<typename T>
    const Memory* copy(const T* data, uint32_t size) {
        // Placeholder implementation
        return nullptr;
    }
    
    // Shader loading helpers
    Memory* alloc(uint32_t size);
    void release(const Memory* mem);
}

// Global bgfx instance (simplified for our needs)
extern bgfx::Init g_bgfxInit;