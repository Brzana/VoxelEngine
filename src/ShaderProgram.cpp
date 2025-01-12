#include "../include/ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>

ShaderProgram::ShaderProgram()
    : m_programID(0)
{
}

ShaderProgram::~ShaderProgram()
{
    if (m_programID != 0) {
        glDeleteProgram(m_programID);
    }
}

bool ShaderProgram::load(const std::string& vertPath, const std::string& fragPath)
{
    // --- 1) Read vertex shader file ---
    std::ifstream vertFile(vertPath);
    if (!vertFile.is_open()) {
        std::cerr << "Error: Could not open vertex shader file: " << vertPath << std::endl;
        return false;
    }
    std::stringstream vertStream;
    vertStream << vertFile.rdbuf();
    std::string vertSource = vertStream.str();
    vertFile.close();

    // --- 2) Read fragment shader file ---
    std::ifstream fragFile(fragPath);
    if (!fragFile.is_open()) {
        std::cerr << "Error: Could not open fragment shader file: " << fragPath << std::endl;
        return false;
    }
    std::stringstream fragStream;
    fragStream << fragFile.rdbuf();
    std::string fragSource = fragStream.str();
    fragFile.close();

    // --- 3) Compile vertex shader ---
    GLuint vertShader = compileShader(vertSource, GL_VERTEX_SHADER);
    if (vertShader == 0) {
        return false; // Error already logged
    }

    // --- 4) Compile fragment shader ---
    GLuint fragShader = compileShader(fragSource, GL_FRAGMENT_SHADER);
    if (fragShader == 0) {
        glDeleteShader(vertShader);
        return false; // Error already logged
    }

    // --- 5) Create program and link ---
    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertShader);
    glAttachShader(m_programID, fragShader);
    glLinkProgram(m_programID);

    // --- Check linking errors ---
    GLint success;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_programID, 512, nullptr, infoLog);
        std::cerr << "Error: Program linking failed:\n" << infoLog << std::endl;
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
        glDeleteProgram(m_programID);
        m_programID = 0;
        return false;
    }

    // --- Cleanup individual shaders ---
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return true;
}

void ShaderProgram::use()
{
    if (m_programID != 0) {
        glUseProgram(m_programID);
    }
}

void ShaderProgram::unuse()
{
    glUseProgram(0);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& mat)
{
    GLint loc = glGetUniformLocation(m_programID, name.c_str());
    if (loc != -1) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
    }
}

void ShaderProgram::setUniform(const std::string& name, int value)
{
    GLint loc = glGetUniformLocation(m_programID, name.c_str());
    if (loc != -1) {
        glUniform1i(loc, value);
    }
}

void ShaderProgram::setUniform(const std::string& name, float value)
{
    GLint loc = glGetUniformLocation(m_programID, name.c_str());
    if (loc != -1) {
        glUniform1f(loc, value);
    }
}

GLuint ShaderProgram::compileShader(const std::string& source, GLenum type)
{
    GLuint shader = glCreateShader(type);
    const char* srcPtr = source.c_str();
    glShaderSource(shader, 1, &srcPtr, nullptr);
    glCompileShader(shader);

    // Check for compile errors
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Error: Shader compilation failed:\n" << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}
