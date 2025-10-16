#include "OpenGLShaderProgram.h"
#include <glad/glad.h>

namespace pap
{

static void CheckCompileErrors(GLuint object, const std::string &type)
{
    GLint success;
    GLchar infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            std::cerr << "Shader compilation error [" << type << "]:\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);
            std::cerr << "Program linking error:\n" << infoLog << std::endl;
        }
    }
}

static GLuint CompileShader(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    CheckCompileErrors(shader, (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"));
    return shader;
}

OpenGLShaderProgram::OpenGLShaderProgram(const std::filesystem::path &vertexPath,
                                         const std::filesystem::path &fragmentPath)
{
    std::string vertSource = ReadTextFile(vertexPath);
    std::string fragSource = ReadTextFile(fragmentPath);

    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertSource);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragSource);

    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vs);
    glAttachShader(m_RendererID, fs);
    glLinkProgram(m_RendererID);
    CheckCompileErrors(m_RendererID, "PROGRAM");

    glDetachShader(m_RendererID, vs);
    glDetachShader(m_RendererID, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
}

OpenGLShaderProgram::~OpenGLShaderProgram()
{
    glDeleteProgram(m_RendererID);
}

void OpenGLShaderProgram::Bind() const
{
    glUseProgram(m_RendererID);
}

void OpenGLShaderProgram::Unbind() const
{
    glUseProgram(0);
}


int OpenGLShaderProgram::GetLocation(const std::string &name) const
{
    auto it = m_UniformLocationCache.find(name);
    if (it != m_UniformLocationCache.end())
        return it->second;

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        std::cerr << "Warning: uniform '" << name << "' doesn't exist!\n";
    m_UniformLocationCache[name] = location;
    return location;
}


// -----------------------------
// Float uniforms
// -----------------------------
void OpenGLShaderProgram::SetUniform1f(const std::string &name, float value)
{
    glUniform1f(GetLocation(name), value);
}
void OpenGLShaderProgram::SetUniform2f(const std::string &name, float v0, float v1)
{
    glUniform2f(GetLocation(name), v0, v1);
}
void OpenGLShaderProgram::SetUniform3f(const std::string &name, float v0, float v1, float v2)
{
    glUniform3f(GetLocation(name), v0, v1, v2);
}
void OpenGLShaderProgram::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetLocation(name), v0, v1, v2, v3);
}

// -----------------------------
// Int uniforms
// -----------------------------
void OpenGLShaderProgram::SetUniform1i(const std::string &name, int value)
{
    glUniform1i(GetLocation(name), value);
}
void OpenGLShaderProgram::SetUniform2i(const std::string &name, int v0, int v1)
{
    glUniform2i(GetLocation(name), v0, v1);
}
void OpenGLShaderProgram::SetUniform3i(const std::string &name, int v0, int v1, int v2)
{
    glUniform3i(GetLocation(name), v0, v1, v2);
}
void OpenGLShaderProgram::SetUniform4i(const std::string &name, int v0, int v1, int v2, int v3)
{
    glUniform4i(GetLocation(name), v0, v1, v2, v3);
}

// -----------------------------
// Vector / array uniforms
// -----------------------------
void OpenGLShaderProgram::SetUniform1fv(const std::string &name, const float *values, uint32_t count)
{
    glUniform1fv(GetLocation(name), count, values);
}
void OpenGLShaderProgram::SetUniform2fv(const std::string &name, const float *values, uint32_t count)
{
    glUniform2fv(GetLocation(name), count, values);
}
void OpenGLShaderProgram::SetUniform3fv(const std::string &name, const float *values, uint32_t count)
{
    glUniform3fv(GetLocation(name), count, values);
}
void OpenGLShaderProgram::SetUniform4fv(const std::string &name, const float *values, uint32_t count)
{
    glUniform4fv(GetLocation(name), count, values);
}

void OpenGLShaderProgram::SetUniform1iv(const std::string &name, const int *values, uint32_t count)
{
    glUniform1iv(GetLocation(name), count, values);
}
void OpenGLShaderProgram::SetUniform2iv(const std::string &name, const int *values, uint32_t count)
{
    glUniform2iv(GetLocation(name), count, values);
}
void OpenGLShaderProgram::SetUniform3iv(const std::string &name, const int *values, uint32_t count)
{
    glUniform3iv(GetLocation(name), count, values);
}
void OpenGLShaderProgram::SetUniform4iv(const std::string &name, const int *values, uint32_t count)
{
    glUniform4iv(GetLocation(name), count, values);
}

// -----------------------------
// Matrix uniforms
// -----------------------------
void OpenGLShaderProgram::SetUniformMat2(const std::string &name, const float *matrix, bool transpose)
{
    glUniformMatrix2fv(GetLocation(name), 1, transpose ? GL_TRUE : GL_FALSE, matrix);
}
void OpenGLShaderProgram::SetUniformMat3(const std::string &name, const float *matrix, bool transpose)
{
    glUniformMatrix3fv(GetLocation(name), 1, transpose ? GL_TRUE : GL_FALSE, matrix);
}
void OpenGLShaderProgram::SetUniformMat4(const std::string &name, const float *matrix, bool transpose)
{
    glUniformMatrix4fv(GetLocation(name), 1, transpose ? GL_TRUE : GL_FALSE, matrix);
}

} // namespace pap
