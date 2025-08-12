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