
#include "OpenGLBuffer.h"
#include "pinepch.h"
#include <glad/glad.h>

namespace pap
{

// VertexBuffer //////////////////////////////////////////////////////////////////////////////

OpenGLVertexBuffer::OpenGLVertexBuffer(const void *data, size_t size)
{
    glCreateBuffers(1, &m_RendererID);
    glNamedBufferData(m_RendererID, size, data, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetData(const void *data, size_t size)
{
    glNamedBufferSubData(m_RendererID, 0, size, data);
}

void OpenGLVertexBuffer::BindToVAO(uint32_t vao, uint32_t bindingIndex, uint32_t stride) const
{
    glVertexArrayVertexBuffer(vao, bindingIndex, m_RendererID, 0, stride);
}


// Indexbuffer //////////////////////////////////////////////////////////////////////////////

OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t *indices, uint32_t count) : m_Count(count)
{
    glCreateBuffers(1, &m_RendererID);
    glNamedBufferData(m_RendererID, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t OpenGLIndexBuffer::GetCount() const
{
    return m_Count;
}
} // namespace pap
