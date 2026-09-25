#pragma once

#include "glad/glad.h"
#include "file.h"

#include <string>
#include <cstdio>

struct Shader
{
    GLuint program = 0;

    /// @brief Initializes the shader program from vertex and fragment shader files.
    /// @param vertPath Path to the vertex shader source file.
    /// @param fragPath Path to the fragment shader source file.
    /// @return true if the shader program was successfully created and linked, false otherwise.
    bool init(const std::string &vertPath, const std::string &fragPath)
    {
        auto vertSource = File::read(vertPath);
        if (!vertSource)
        {
            fprintf(stderr, "failed to read vertex shader file: %s\n", vertPath.c_str());
            return false;
        }

        auto fragSource = File::read(fragPath);
        if (!fragSource)
        {
            fprintf(stderr, "failed to read fragment shader file: %s\n", fragPath.c_str());
            return false;
        }

        // Create and compile the vertex shader
        GLuint vertShader = createShader(GL_VERTEX_SHADER, vertSource->c_str());
        if (!vertShader)
            return false;

        // Create and compile the fragment shader
        GLuint fragShader = createShader(GL_FRAGMENT_SHADER, fragSource->c_str());
        if (!fragShader)
            return false;

        // Create the shader program
        program = glCreateProgram();
        if (!program)
        {
            fprintf(stderr, "failed to create program\n");
            return false;
        }

        // Attach both shaders and link them into a program
        glAttachShader(program, vertShader);
        glAttachShader(program, fragShader);
        glLinkProgram(program);

        // Check whether the program linked successfully
        if (!programLinked())
            return false;

        // Shaders are no longer needed after they have been linked
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        return true;
    }

    /// @brief Creates and compiles a shader from the provided source code.
    /// @param type OpenGL shader type, such as GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
    /// @param source Null-terminated shader source code.
    /// @return shader object ID if compilation succeeds, 0 otherwise.
    GLuint createShader(GLenum type, const char *source)
    {
        GLuint shader = glCreateShader(type);

        if (shader == GL_INVALID_ENUM)
        {
            fprintf(stderr, "invalid enum type for shader\n");
            return 0;
        }

        if (!shader)
        {
            fprintf(stderr, "failed to create shader\n");
            return 0;
        }

        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        if (!shaderCompiled(shader))
        {
            return 0;
        }

        return shader;
    }

    /// @brief Checks whether a shader compiled successfully and prints the error log on failure.
    /// @param shader OpenGL shader object ID to check.
    /// @return true if the shader compiled successfully, false otherwise.
    bool shaderCompiled(GLuint shader)
    {
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            GLsizei logLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

            std::string infoLog(logLength, '\0');
            glGetShaderInfoLog(shader, logLength, nullptr, infoLog.data());

            fprintf(stderr, "shader compilation failed: %s\n", infoLog.c_str());
            return false;
        }

        return true;
    }

    /// @brief Checks whether the shader program linked successfully and prints the error log on failure.
    /// @return true if the program linked successfully, false otherwise.
    bool programLinked()
    {
        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (!success)
        {
            GLsizei logLength;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

            std::string infoLog(logLength, '\0');
            glGetProgramInfoLog(program, logLength, nullptr, infoLog.data());

            fprintf(stderr, "failed to link program: %s\n", infoLog.c_str());
            return false;
        }

        return true;
    }

    /// @brief Sets this shader program as the active OpenGL program.
    void useProgram() const
    {
        glUseProgram(program);
    }
};
