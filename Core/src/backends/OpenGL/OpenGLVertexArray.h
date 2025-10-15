#pragma once

#include "renderer/VertexArray.h"

namespace pap
{

class OpenGLVertexArray : public VertexArray
{
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) override;
    void SetIndexBuffer(const IndexBuffer* ib) override;
    IndexBuffer* GetIndexBuffer() const override;

private:
    uint32_t m_RendererID = 0;
    const VertexBuffer* m_VertexBuffer = nullptr; // non-owning
    const IndexBuffer* m_IndexBuffer   = nullptr; // non-owning
};
} // namespace pap
