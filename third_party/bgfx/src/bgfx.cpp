#include "bgfx/bgfx.h"
#include <cstdlib>
#include <cstring>

// Global bgfx instance
bgfx::Init g_bgfxInit;

namespace bgfx {
    // Stub implementations for bgfx functions
    
    bool init(const Init& init) {
        g_bgfxInit = init;
        return true;
    }
    
    void shutdown() {
        // Cleanup code would go here
    }
    
    void frame() {
        // Frame processing would go here
    }
    
    void setViewClear(uint8_t viewId, uint16_t flags, uint32_t rgba, float depth, uint8_t stencil) {
        // View clear would go here
    }
    
    void setViewRect(uint8_t viewId, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
        // View rect would go here
    }
    
    void setState(uint64_t state) {
        // State setting would go here
    }
    
    void setProgram(ProgramHandle program) {
        // Program setting would go here
    }
    
    void setUniform(UniformHandle uniform, const void* value) {
        // Uniform setting would go here
    }
    
    void setVertexBuffer(uint8_t stream, VertexBufferHandle handle) {
        // Vertex buffer setting would go here
    }
    
    void setIndexBuffer(IndexBufferHandle handle) {
        // Index buffer setting would go here
    }
    
    void submit(uint8_t viewId) {
        // Submit would go here
    }
    
    // Shader creation
    ShaderHandle createShader(const Memory* mem) {
        ShaderHandle handle;
        handle.idx = 1; // Simple ID assignment
        return handle;
    }
    
    ShaderHandle createShader(const std::string& vertexShader, const std::string& fragmentShader) {
        ShaderHandle handle;
        handle.idx = 1; // Simple ID assignment
        return handle;
    }
    
    // Program creation
    ProgramHandle createProgram(ShaderHandle vertexShader, ShaderHandle fragmentShader) {
        ProgramHandle handle;
        handle.idx = 1; // Simple ID assignment
        return handle;
    }
    
    // Buffer creation
    VertexBufferHandle createVertexBuffer(const Memory* mem, const VertexLayout& layout) {
        VertexBufferHandle handle;
        handle.idx = 1; // Simple ID assignment
        return handle;
    }
    
    IndexBufferHandle createIndexBuffer(const Memory* mem) {
        IndexBufferHandle handle;
        handle.idx = 1; // Simple ID assignment
        return handle;
    }
    
    UniformHandle createUniform(const char* name, UniformType type) {
        UniformHandle handle;
        handle.idx = 1; // Simple ID assignment
        return handle;
    }
    
    // Handle validation functions
    bool isValid(ShaderHandle handle) {
        return handle.idx != BGFX_INVALID_HANDLE;
    }
    
    bool isValid(ProgramHandle handle) {
        return handle.idx != BGFX_INVALID_HANDLE;
    }
    
    bool isValid(VertexBufferHandle handle) {
        return handle.idx != BGFX_INVALID_HANDLE;
    }
    
    bool isValid(IndexBufferHandle handle) {
        return handle.idx != BGFX_INVALID_HANDLE;
    }
    
    bool isValid(UniformHandle handle) {
        return handle.idx != BGFX_INVALID_HANDLE;
    }
    
    // Cleanup functions
    void destroy(ShaderHandle handle) {
        // Cleanup would go here
    }
    
    void destroy(ProgramHandle handle) {
        // Cleanup would go here
    }
    
    void destroy(VertexBufferHandle handle) {
        // Cleanup would go here
    }
    
    void destroy(IndexBufferHandle handle) {
        // Cleanup would go here
    }
    
    void destroy(UniformHandle handle) {
        // Cleanup would go here
    }
    
    // Shader loading helpers
    Memory* alloc(uint32_t size) {
        Memory* mem = new Memory;
        mem->data = new uint8_t[size];
        mem->size = size;
        return mem;
    }
    
    void release(const Memory* mem) {
        if (mem) {
            delete[] mem->data;
            delete mem;
        }
    }
    

}