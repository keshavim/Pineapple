#include "VertexArray.h"
#include "Renderer.h"
#include "pinepch.h"

#include "backends/OpenGL/OpenGLVertexArray.h"


namespace pap
{

// ================= Factory =================
VertexArray *VertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::None:
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLVertexArray();
    }
}
} // namespace pap
