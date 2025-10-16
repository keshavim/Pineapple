#pragma once
#include "renderer/ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

//opengl implementaion of the shaderprogram
namespace pap
{

class OpenGLShaderProgram : public ShaderProgram
{
public:
    OpenGLShaderProgram(const std::filesystem::path& vertexPath,
                        const std::filesystem::path& fragmentPath);
    virtual ~OpenGLShaderProgram();

    void Bind() const override;
    void Unbind() const override;

    // -----------------------------
// Float uniforms
// -----------------------------
virtual void SetUniform1f(const std::string& name, float value)override;
virtual void SetUniform2f(const std::string& name, float v0, float v1) override;
virtual void SetUniform3f(const std::string& name, float v0, float v1, float v2)override;
virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)override;

// -----------------------------
// Int uniforms
// -----------------------------
virtual void SetUniform1i(const std::string& name, int value) override;
virtual void SetUniform2i(const std::string& name, int v0, int v1)override;
virtual void SetUniform3i(const std::string& name, int v0, int v1, int v2) override;
virtual void SetUniform4i(const std::string& name, int v0, int v1, int v2, int v3) override;

// -----------------------------
// Vector / array overloads
// -----------------------------
virtual void SetUniform1fv(const std::string& name, const float* values, uint32_t count)override;
virtual void SetUniform2fv(const std::string& name, const float* values, uint32_t count) override;
virtual void SetUniform3fv(const std::string& name, const float* values, uint32_t count) override;
virtual void SetUniform4fv(const std::string& name, const float* values, uint32_t count) override;

virtual void SetUniform1iv(const std::string& name, const int* values, uint32_t count) override;
virtual void SetUniform2iv(const std::string& name, const int* values, uint32_t count) override;
virtual void SetUniform3iv(const std::string& name, const int* values, uint32_t count) override;
virtual void SetUniform4iv(const std::string& name, const int* values, uint32_t count) override;

// -----------------------------
// Matrix uniforms
// -----------------------------
virtual void SetUniformMat2(const std::string& name, const float* matrix, bool transpose = false) override;
virtual void SetUniformMat3(const std::string& name, const float* matrix, bool transpose = false) override;
virtual void SetUniformMat4(const std::string& name, const float* matrix, bool transpose = false) override;


private:
    uint32_t m_RendererID = 0;

    mutable std::unordered_map<std::string, int> m_UniformLocationCache;

    int GetLocation(const std::string& name) const;

};

} // namespace pap
