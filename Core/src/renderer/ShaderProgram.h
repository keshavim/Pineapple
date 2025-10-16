#pragma once
#include "core/core.h"
#include <filesystem>
#include <string>
#include <vector>

namespace pap
{

class ShaderProgram
{
public:
    virtual ~ShaderProgram() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    // -----------------------------
    // Float uniforms
    // -----------------------------
    virtual void SetUniform1f(const std::string &name, float value) = 0;
    virtual void SetUniform2f(const std::string &name, float v0, float v1) = 0;
    virtual void SetUniform3f(const std::string &name, float v0, float v1, float v2) = 0;
    virtual void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) = 0;

    // -----------------------------
    // Int uniforms
    // -----------------------------
    virtual void SetUniform1i(const std::string &name, int value) = 0;
    virtual void SetUniform2i(const std::string &name, int v0, int v1) = 0;
    virtual void SetUniform3i(const std::string &name, int v0, int v1, int v2) = 0;
    virtual void SetUniform4i(const std::string &name, int v0, int v1, int v2, int v3) = 0;

    // -----------------------------
    // Vector / array overloads
    // -----------------------------
    virtual void SetUniform1fv(const std::string &name, const float *values, uint32_t count) = 0;
    virtual void SetUniform2fv(const std::string &name, const float *values, uint32_t count) = 0;
    virtual void SetUniform3fv(const std::string &name, const float *values, uint32_t count) = 0;
    virtual void SetUniform4fv(const std::string &name, const float *values, uint32_t count) = 0;

    virtual void SetUniform1iv(const std::string &name, const int *values, uint32_t count) = 0;
    virtual void SetUniform2iv(const std::string &name, const int *values, uint32_t count) = 0;
    virtual void SetUniform3iv(const std::string &name, const int *values, uint32_t count) = 0;
    virtual void SetUniform4iv(const std::string &name, const int *values, uint32_t count) = 0;

    // -----------------------------
    // Matrix uniforms
    // -----------------------------
    virtual void SetUniformMat2(const std::string &name, const float *matrix, bool transpose = false) = 0;
    virtual void SetUniformMat3(const std::string &name, const float *matrix, bool transpose = false) = 0;
    virtual void SetUniformMat4(const std::string &name, const float *matrix, bool transpose = false) = 0;


    static ShaderProgram *Create(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath);
};


} // namespace pap
