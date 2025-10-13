#ifndef RENDERER_H
#define RENDERER_H

#include "backends/RendererBackend.h"

namespace pap
{

class Renderer
{
public:
    Renderer() = delete;

    static bool Init(const RendererInitInfo& info);
    static void Shutdown();

    static void BeginFrame();
    static void EndFrame();
    static void Resize(int width, int height);

    static RendererBackendType GetBackendType();

    static IRendererBackend* GetBackend();

private:
    static inline std::unique_ptr<IRendererBackend> s_Backend = nullptr;
};

} // namespace pap

#endif
