#include "pinepch.h"

#include "Buffer.h"
#include "Renderer.h"

#include "backends/OpenGL/OpenGLBuffer.h"

namespace pap
{


VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::None:
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLVertexBuffer(vertices, size);
    }
}

IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::None:
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLIndexBuffer(indices, size);
    }
}

} // namespace pap
