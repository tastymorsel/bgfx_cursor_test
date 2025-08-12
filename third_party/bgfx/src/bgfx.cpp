#include "bgfx/bgfx.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

// Global bgfx instance
bgfx::Init g_bgfxInit;

namespace bgfx {
    // Stub implementations for bgfx functions
    
    bool init(const Init& init) {
        g_bgfxInit = init;
        std::cout << "bgfx::init called with resolution: " << init.resolution.width << "x" << init.resolution.height << std::endl;
        return true;
    }
    
    void shutdown() {
        std::cout << "bgfx::shutdown called" << std::endl;
    }
    
    void frame() {
        // Frame processing would go here
    }
    
    void setViewClear(uint8_t viewId, uint16_t flags, uint32_t rgba, float depth, uint8_t stencil) {
        // View clear would go here
        std::cout << "bgfx::setViewClear called with rgba: 0x" << std::hex << rgba << std::dec << std::endl;
    }
    
    void setViewRect(uint8_t viewId, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
        // View rect would go here
    }
    
    void setState(uint64_t state) {
        // State setting would go here
    }
    
    void setProgram(ProgramHandle program) {
        // Program setting would go here
        std::cout << "bgfx::setProgram called with program handle: " << program.idx << std::endl;
    }
    
    void setUniform(UniformHandle uniform, const void* value) {
        // Uniform setting would go here
        std::cout << "bgfx::setUniform called with uniform handle: " << uniform.idx << std::endl;
    }
    
    void setVertexBuffer(uint8_t stream, VertexBufferHandle handle) {
        // Vertex buffer setting would go here
        std::cout << "bgfx::setVertexBuffer called with handle: " << handle.idx << std::endl;
    }
    
    void setIndexBuffer(IndexBufferHandle handle) {
        // Index buffer setting would go here
        std::cout << "bgfx::setIndexBuffer called with handle: " << handle.idx << std::endl;
    }
    
    void submit(uint8_t viewId) {
        // Submit would go here
        std::cout << "bgfx::submit called for view: " << (int)viewId << std::endl;
    }
    
    // Shader creation
    ShaderHandle createShader(const Memory* mem) {
        ShaderHandle handle;
        handle.idx = 1; // Simple ID assignment
        std::cout << "bgfx::createShader called, returning handle: " << handle.idx << std::endl;
        return handle;
    }
    
    ShaderHandle createShader(const std::string& vertexShader, const std::string& fragmentShader) {
        ShaderHandle handle;
        handle.idx = 1; // Simple ID assignment
        std::cout << "bgfx::createShader called with " << vertexShader << " and " << fragmentShader << ", returning handle: " << handle.idx << std::endl;
        return handle;
    }
    
    // Program creation
    ProgramHandle createProgram(ShaderHandle vertexShader, ShaderHandle fragmentShader) {
        ProgramHandle handle;
        handle.idx = 1; // Simple ID assignment
        std::cout << "bgfx::createProgram called, returning handle: " << handle.idx << std::endl;
        return handle;
    }
    
    // Buffer creation
    VertexBufferHandle createVertexBuffer(const Memory* mem, const VertexLayout& layout) {
        VertexBufferHandle handle;
        handle.idx = 1; // Simple ID assignment
        std::cout << "bgfx::createVertexBuffer called, returning handle: " << handle.idx << std::endl;
        return handle;
    }
    
    IndexBufferHandle createIndexBuffer(const Memory* mem) {
        IndexBufferHandle handle;
        handle.idx = 1; // Simple ID assignment
        std::cout << "bgfx::createIndexBuffer called, returning handle: " << handle.idx << std::endl;
        return handle;
    }
    
    UniformHandle createUniform(const char* name, UniformType type) {
        UniformHandle handle;
        handle.idx = 1; // Simple ID assignment
        std::cout << "bgfx::createUniform called with name: " << name << ", returning handle: " << handle.idx << std::endl;
        return handle;
    }
    
    // Handle validation functions
    bool isValid(ShaderHandle handle) {
        bool valid = handle.idx != BGFX_INVALID_HANDLE;
        std::cout << "bgfx::isValid(ShaderHandle) called with handle: " << handle.idx << ", returning: " << (valid ? "true" : "false") << std::endl;
        return valid;
    }
    
    bool isValid(ProgramHandle handle) {
        bool valid = handle.idx != BGFX_INVALID_HANDLE;
        std::cout << "bgfx::isValid(ProgramHandle) called with handle: " << handle.idx << ", returning: " << (valid ? "true" : "false") << std::endl;
        return valid;
    }
    
    bool isValid(VertexBufferHandle handle) {
        bool valid = handle.idx != BGFX_INVALID_HANDLE;
        std::cout << "bgfx::isValid(VertexBufferHandle) called with handle: " << handle.idx << ", returning: " << (valid ? "true" : "false") << std::endl;
        return valid;
    }
    
    bool isValid(IndexBufferHandle handle) {
        bool valid = handle.idx != BGFX_INVALID_HANDLE;
        std::cout << "bgfx::isValid(IndexBufferHandle) called with handle: " << handle.idx << ", returning: " << (valid ? "true" : "false") << std::endl;
        return valid;
    }
    
    bool isValid(UniformHandle handle) {
        bool valid = handle.idx != BGFX_INVALID_HANDLE;
        std::cout << "bgfx::isValid(UniformHandle) called with handle: " << handle.idx << ", returning: " << (valid ? "true" : "false") << std::endl;
        return valid;
    }
    
    // Cleanup functions
    void destroy(ShaderHandle handle) {
        std::cout << "bgfx::destroy(ShaderHandle) called with handle: " << handle.idx << std::endl;
    }
    
    void destroy(ProgramHandle handle) {
        std::cout << "bgfx::destroy(ProgramHandle) called with handle: " << handle.idx << std::endl;
    }
    
    void destroy(VertexBufferHandle handle) {
        std::cout << "bgfx::destroy(VertexBufferHandle) called with handle: " << handle.idx << std::endl;
    }
    
    void destroy(IndexBufferHandle handle) {
        std::cout << "bgfx::destroy(IndexBufferHandle) called with handle: " << handle.idx << std::endl;
    }
    
    void destroy(UniformHandle handle) {
        std::cout << "bgfx::destroy(UniformHandle) called with handle: " << handle.idx << std::endl;
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