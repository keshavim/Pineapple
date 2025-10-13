#ifndef RENDERER_BACKEND_H
#define RENDERER_BACKEND_H

#include <string>
#include <memory>
#include "core/core.h"

namespace pap
{

enum class RendererBackendType
{
    None,
    Vulkan,
    OpenGL,
    DirectX,
    Metal
};

struct RendererInitInfo
{
    void* windowHandle = nullptr;
    int width = 0;
    int height = 0;
    RendererBackendType backend = RendererBackendType::None;
};

class IRendererBackend
{
public:
    virtual ~IRendererBackend() = default;

    virtual bool Init(const RendererInitInfo& info) = 0;
    virtual void Shutdown() = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    virtual void Resize(int width, int height) = 0;

    virtual RendererBackendType GetBackendType() const = 0;
};

} // namespace pap

#endif
