#pragma once

#include "renderer/RendererContext.h"


struct GLFWwindow;
namespace pap
{

class OpenGLContext : public RendererContext
{
public:
    OpenGLContext(GLFWwindow *windowhandle);

    virtual void Init() override;
    virtual void SwapBuffers() override;

private:
    GLFWwindow *m_windowhandle;
};
} // namespace pap
