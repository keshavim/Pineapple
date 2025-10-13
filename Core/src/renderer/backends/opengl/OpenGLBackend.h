#ifndef OPENGL_BACKEND_H
#define OPENGL_BACKEND_H

#include "../RendererBackend.h"

namespace pap
{

class OpenGLBackend : public IRendererBackend
{
public:
    bool Init(const RendererInitInfo& info) override;
    void Shutdown() override;

    void BeginFrame() override;
    void EndFrame() override;
    void Resize(int width, int height) override;

    RendererBackendType GetBackendType() const override { return RendererBackendType::OpenGL; }

private:
    void* m_WindowHandle = nullptr;
    int m_Width = 0;
    int m_Height = 0;
};

} // namespace pap

#endif
