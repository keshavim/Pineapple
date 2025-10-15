#pragma once
#include "renderer/Buffer.h"

namespace pap
{

class OpenGLVertexBuffer : public VertexBuffer
{
public:
    OpenGLVertexBuffer(const void *data, size_t size);

    virtual ~OpenGLVertexBuffer();

    void Bind() const override;

    void Unbind() const override;

    void SetData(const void *data, size_t size) override;

    void BindToVAO(uint32_t vao, uint32_t bindingIndex, uint32_t stride) override;

    inline uint32_t GetID() override {return m_RendererID;}

private:
    uint32_t m_RendererID;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
    OpenGLIndexBuffer(const uint32_t *indices, uint32_t count);

    virtual ~OpenGLIndexBuffer();

    void Bind() const override;

    void Unbind() const override;

    uint32_t GetCount() const override;

private:
    uint32_t m_RendererID;
    uint32_t m_Count;
};
} // namespace pap
