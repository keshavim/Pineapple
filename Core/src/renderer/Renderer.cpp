#include "Renderer.h"
//#include "VulkanBackend.h"
#include "pinepch.h"
#include "backends/opengl/OpenGLBackend.h"

namespace pap
{

bool Renderer::Init(const RendererInitInfo& info)
{
    switch (info.backend)
    {
        // case RendererBackendType::Vulkan:
        //     s_Backend = std::make_unique<VulkanBackend>();
        //     break;
        case RendererBackendType::OpenGL:
            s_Backend = std::make_unique<OpenGLBackend>();
            break;
        default:
            PAP_ERROR("Unsupported backend");
            return false;
    }

    return s_Backend->Init(info);
}

void Renderer::Shutdown()
{
    if (s_Backend)
    {
        s_Backend->Shutdown();
        s_Backend.reset();
    }
}

void Renderer::BeginFrame()
{
    if (s_Backend) s_Backend->BeginFrame();
}

void Renderer::EndFrame()
{
    if (s_Backend) s_Backend->EndFrame();
}

void Renderer::Resize(int width, int height)
{
    if (s_Backend) s_Backend->Resize(width, height);
}

RendererBackendType Renderer::GetBackendType()
{
    if (!s_Backend) return RendererBackendType::None;
    return s_Backend->GetBackendType();
}

IRendererBackend* Renderer::GetBackend()
{
    return s_Backend.get();
}

} // namespace pap
