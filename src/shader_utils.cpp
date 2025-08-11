#include "shader_utils.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace ShaderUtils {

bool LoadShader(const std::string& filename, std::string& source) {
    std::string filepath = GetShaderPath(filename);
    
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
        return false;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    source = buffer.str();
    
    return true;
}

bgfx::ShaderHandle CreateShader(const std::string& filename) {
    std::string source;
    if (!LoadShader(filename, source)) {
        return bgfx::ShaderHandle{bgfx::BGFX_INVALID_HANDLE};
    }
    
    bgfx::ShaderHandle handle = bgfx::createShader(
        bgfx::copy(source.c_str(), source.length())
    );
    
    if (!bgfx::isValid(handle)) {
        std::cerr << "Failed to create shader: " << filename << std::endl;
    }
    
    return handle;
}

bgfx::ProgramHandle CreateProgram(const std::string& vertexShader, const std::string& fragmentShader) {
    bgfx::ShaderHandle vs = CreateShader(vertexShader);
    bgfx::ShaderHandle fs = CreateShader(fragmentShader);
    
    if (!bgfx::isValid(vs) || !bgfx::isValid(fs)) {
        return bgfx::ProgramHandle{bgfx::BGFX_INVALID_HANDLE};
    }
    
    bgfx::ProgramHandle program = bgfx::createProgram(vs, fs);
    
    if (!bgfx::isValid(program)) {
        std::cerr << "Failed to create program from " << vertexShader << " and " << fragmentShader << std::endl;
    }
    
    return program;
}

bool CompileShader(const std::string& source, bgfx::ShaderHandle& handle) {
    handle = bgfx::createShader(
        bgfx::copy(source.c_str(), source.length())
    );
    
    return bgfx::isValid(handle);
}

void PrintShaderInfoLog(bgfx::ShaderHandle handle) {
    // bgfx doesn't provide shader info logs in the same way as OpenGL
    // This is a placeholder for debugging purposes
}

std::string GetShaderPath(const std::string& filename) {
    return "assets/shaders/" + filename;
}

bool FileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

void CheckGLError(const std::string& operation) {
    // This is OpenGL specific, not needed for bgfx
    // Kept for compatibility
}

} // namespace ShaderUtils