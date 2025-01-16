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

    void setUniform(const std::string& name, const glm::mat4& mat);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, float value);

private:
    unsigned int m_programID;

    unsigned int compileShader(const std::string& source, unsigned int type);
};