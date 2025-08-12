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
    
    // Constants - using modern names that are more likely to exist in real bgfx
    static const uint16_t kInvalidHandle = 0xFFFF;
    
    // Uniform types
    enum UniformType {
        Vec4,
        Mat4
    };
    
    // States - using modern enum names
    enum StateFlags {
        WriteRgb = 0x00000001,
        WriteA = 0x00000002,
        DepthTestAlways = 0x00000004,
        BlendAlpha = 0x00000008
    };
    
    // Clear flags - using modern enum names
    enum ClearFlags {
        Color = 0x00000001,
        Depth = 0x00000002
    };
    
    // Reset flags - using modern enum names
    enum ResetFlags {
        Vsync = 0x00000001
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
    bool isValid(T handle) { return handle.idx != kInvalidHandle; }
    
    // Shader creation
    ShaderHandle createShader(const Memory* mem);
    ShaderHandle createShader(const std::string& vertexShader, const std::string& fragmentShader);
    
    // Program creation
    ProgramHandle createProgram(ShaderHandle vertexShader, ShaderHandle fragmentShader);
    
    // Buffer creation
    VertexBufferHandle createVertexBuffer(const Memory* mem, const VertexLayout& layout);
    IndexBufferHandle createIndexBuffer(const Memory* mem);
    
    // Uniform creation
    UniformHandle createUniform(const char* name, UniformType type);
    
    // Cleanup functions
    void destroy(ShaderHandle handle);
    void destroy(ProgramHandle handle);
    void destroy(VertexBufferHandle handle);
    void destroy(IndexBufferHandle handle);
    void destroy(UniformHandle handle);
    
    // Shader loading helpers
    Memory* alloc(uint32_t size);
    void release(const Memory* mem);
    
    // Copy function
    template<typename T>
    const Memory* copy(const T* data, uint32_t size) {
        // Placeholder implementation
        return nullptr;
    }
}

// Global bgfx instance (simplified for our needs)
extern bgfx::Init g_bgfxInit;