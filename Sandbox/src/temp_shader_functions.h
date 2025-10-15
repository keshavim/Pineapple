#pragma once
#include <filesystem>
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>



namespace fs = std::filesystem;

namespace render {


// ======================================================
// Read entire file content into a string
// ======================================================
static std::string ReadTextFile(const fs::path& path)
    {
        fs::path fullPath = path;

        // If the path is relative, make it relative to the current source file
        if (path.is_relative())
        {
            fs::path sourceDir = fs::path(__FILE__).parent_path();
            fullPath = sourceDir / path;
        }

        std::ifstream file(fullPath);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file: " << fullPath << std::endl;
            return {};
        }

        std::ostringstream contentStream;
        contentStream << file.rdbuf();
        return contentStream.str();
    }

// ======================================================
// Check shader compilation / program linking errors
// ======================================================
void CheckCompileErrors(GLuint shader, const std::string& type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

uint32_t CreateGraphicsShader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
	{
		std::string vertexShaderSource = ReadTextFile(vertexPath);
		std::string fragmentShaderSource = ReadTextFile(fragmentPath);

		// Vertex shader

		GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = (const GLchar*)vertexShaderSource.c_str();
		glShaderSource(vertexShaderHandle, 1, &source, 0);

		glCompileShader(vertexShaderHandle);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShaderHandle, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShaderHandle, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShaderHandle, maxLength, &maxLength, &infoLog[0]);

			std::cerr << infoLog.data() << std::endl;

			glDeleteShader(vertexShaderHandle);
			return -1;
		}

		// Fragment shader

		GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

		source = (const GLchar*)fragmentShaderSource.c_str();
		glShaderSource(fragmentShaderHandle, 1, &source, 0);

		glCompileShader(fragmentShaderHandle);

		isCompiled = 0;
		glGetShaderiv(fragmentShaderHandle, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShaderHandle, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShaderHandle, maxLength, &maxLength, &infoLog[0]);

			std::cerr << infoLog.data() << std::endl;

			glDeleteShader(fragmentShaderHandle);
			return -1;
		}

		// Program linking

		GLuint program = glCreateProgram();
		glAttachShader(program, vertexShaderHandle);
		glAttachShader(program, fragmentShaderHandle);
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			std::cerr << infoLog.data() << std::endl;

			glDeleteProgram(program);
			glDeleteShader(vertexShaderHandle);
			glDeleteShader(fragmentShaderHandle);

			return -1;
		}

		glDetachShader(program, vertexShaderHandle);
		glDetachShader(program, fragmentShaderHandle);
		return program;
	}
}
