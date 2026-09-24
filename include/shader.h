#pragma once

#include <glad/glad.h>
#include <string>
#include "file.h"

class Shader
{
private:
    GLuint m_program;

    GLuint createShader(GLenum shaderType, const char *shaderSource)
    {
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSource, nullptr);

        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            GLint infoLogLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

            std::string infoLog(infoLogLength, '\0');
            glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog.data());

            std::cerr << "Shader compilation failed: " << infoLog << '\n';
        }

        return shader;
    }

    void linkProgram()
    {
        glLinkProgram(m_program);

        GLint success;
        glGetProgramiv(m_program, GL_LINK_STATUS, &success);

        if (!success)
        {
            GLint infoLogLength;
            glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);

            std::string infoLog(infoLogLength, '\0');
            glGetProgramInfoLog(m_program, infoLogLength, nullptr, infoLog.data());

            std::cerr << "Failed to link shader program: " << infoLog << '\n';
        }
    }

public:
    Shader(const std::string &vertShaderPath, const std::string &fragShaderPath)
    {
        m_program = glCreateProgram();

        auto vertSource = readFile(vertShaderPath);
        auto fragSource = readFile(fragShaderPath);

        if (!vertSource || !fragSource)
        {
            return;
        }

        GLuint vertShader = createShader(GL_VERTEX_SHADER, vertSource->c_str());
        GLuint fragShader = createShader(GL_FRAGMENT_SHADER, fragSource->c_str());

        glAttachShader(m_program, vertShader);
        glAttachShader(m_program, fragShader);

        linkProgram();

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
    }

    void use() const
    {
        glUseProgram(m_program);
    }
};
