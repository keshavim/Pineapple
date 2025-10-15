#include "OpenGLVertexArray.h"
#include "pinepch.h"
#include <glad/glad.h>

namespace pap
{

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {
        case ShaderDataType::Float:
        case ShaderDataType::Vec2:
        case ShaderDataType::Vec3:
        case ShaderDataType::Vec4:
            return GL_FLOAT;

        case ShaderDataType::Int:
        case ShaderDataType::IVec2:
        case ShaderDataType::IVec3:
        case ShaderDataType::IVec4:
            return GL_INT;

        case ShaderDataType::Bool:
            return GL_BOOL;
    }

    return 0; // should never happen
}




void VertexBufferLayout::Push(uint32_t count, ShaderDataType type, bool normalized)
{
    Elements.push_back({count, type, normalized, Stride});
    Stride += count * ShaderDataTypeToOpenGLBaseType(type); // extend for other types if needed
}


OpenGLVertexArray::OpenGLVertexArray()
{
    glCreateVertexArrays(1, &m_RendererID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void OpenGLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    // No smart ptr calls — direct reference
    vb.BindToVAO(m_RendererID, 0, layout.Stride);
    m_VertexBuffer = &vb; // just store pointer, no ownership

    uint32_t index = 0;
    for (const auto& element : layout.Elements)
    {
        glEnableVertexArrayAttrib(m_RendererID, index);
        glVertexArrayAttribFormat(
            m_RendererID,
            index,
            element.Count,
            ShaderDataTypeToOpenGLBaseType(element.Type),
            element.Normalized ? GL_TRUE : GL_FALSE,
            static_cast<GLuint>(element.Offset)
        );
        glVertexArrayAttribBinding(m_RendererID, index, 0);
        index++;
    }
}

void OpenGLVertexArray::SetIndexBuffer(const IndexBuffer* ib)
{
    if (ib)
    {
        ib->Bind();
        m_IndexBuffer = ib;
    }
    else
    {
        m_IndexBuffer = nullptr;
    }
}

IndexBuffer* OpenGLVertexArray::GetIndexBuffer() const
{
    return const_cast<IndexBuffer*>(m_IndexBuffer);
}

} // namespace pap
