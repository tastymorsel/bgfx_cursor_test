#pragma once

#include <string>
#include <vector>
#include <bgfx/bgfx.h>

namespace ShaderUtils {
    // Shader loading
    bool LoadShader(const std::string& filename, std::string& source);
    bgfx::ShaderHandle CreateShader(const std::string& filename);
    bgfx::ProgramHandle CreateProgram(const std::string& vertexShader, const std::string& fragmentShader);
    
    // Shader compilation helpers
    bool CompileShader(const std::string& source, bgfx::ShaderHandle& handle);
    void PrintShaderInfoLog(bgfx::ShaderHandle handle);
    
    // File utilities
    std::string GetShaderPath(const std::string& filename);
    bool FileExists(const std::string& filename);
    
    // Error handling
    void CheckGLError(const std::string& operation);
};