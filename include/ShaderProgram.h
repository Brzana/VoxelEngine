#pragma once

#include "../include/OpenGl.h"
#include <string>

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    // Load and compile vertex + fragment shaders from files
    bool load(const std::string& vertPath, const std::string& fragPath);

    // Activate/Deactivate the shader program
    void use();
    void unuse();

    // Set uniforms
    void setUniform(const std::string& name, const glm::mat4& mat);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, float value);
    // Overload as needed for vec3, etc.

private:
    GLuint m_programID;

    // Helper to compile a shader from GLSL source
    GLuint compileShader(const std::string& source, GLenum type);
};