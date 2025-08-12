#pragma once

// Compatibility header for bgfx constants
// This provides constants that work with both the stub and real bgfx library

#include <cstdint>

namespace bgfx_compat {
    // Handle invalid value
    static const uint16_t INVALID_HANDLE = 0xFFFF;
    
    // Reset flags
    static const uint32_t RESET_VSYNC = 0x00000001;
    
    // Clear flags
    static const uint16_t CLEAR_COLOR = 0x00000001;
    static const uint16_t CLEAR_DEPTH = 0x00000002;
    
    // State flags
    static const uint64_t STATE_WRITE_RGB = 0x00000001;
    static const uint64_t STATE_WRITE_A = 0x00000002;
    static const uint64_t STATE_DEPTH_TEST_ALWAYS = 0x00000004;
    static const uint64_t STATE_BLEND_ALPHA = 0x00000008;
    
    // Renderer types
    static const uint8_t RENDERER_TYPE_OPENGL = 0;
    
    // Uniform types
    static const uint8_t UNIFORM_TYPE_VEC4 = 0;
    static const uint8_t UNIFORM_TYPE_MAT4 = 1;
    
    // Vertex attributes
    static const uint8_t ATTRIB_POSITION = 0;
    static const uint8_t ATTRIB_TEXCOORD0 = 1;
    static const uint8_t ATTRIB_TYPE_FLOAT = 0;
}

// Check if we're using the real bgfx library
#ifdef BGFX_CONFIG_DEBUG
    // Real bgfx library detected
    #define USE_REAL_BGFX 1
#else
    // Check if we have the real bgfx header
    #if __has_include(<bgfx/bgfx.h>)
        #include <bgfx/bgfx.h>
        #if defined(bgfx::RendererType) && defined(bgfx::UniformType) && defined(bgfx::Attrib)
            #define USE_REAL_BGFX 1
        #else
            #define USE_REAL_BGFX 0
        #endif
    #else
        #define USE_REAL_BGFX 0
    #endif
#endif

// Provide fallback definitions if real bgfx enums are not available
#if !USE_REAL_BGFX
namespace bgfx {
    enum RendererType {
        OpenGL = 0
    };
    
    enum UniformType {
        Vec4 = 0,
        Mat4 = 1
    };
    
    enum Attrib {
        Position = 0,
        TexCoord0 = 1
    };
    
    enum AttribType {
        Float = 0
    };
}
#endif