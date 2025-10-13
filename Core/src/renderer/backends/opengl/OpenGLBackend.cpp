#include "OpenGLBackend.h"
#include "pinepch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace pap
{

bool OpenGLBackend::Init(const RendererInitInfo& info)
{
    m_WindowHandle = info.windowHandle;
    m_Width = info.width;
    m_Height = info.height;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        PAP_ERROR("Failed to initialize GLAD");
        return false;
    }

    glViewport(0, 0, m_Width, m_Height);
    glEnable(GL_DEPTH_TEST);

    PAP_PRINT("OpenGL initialized");
    PAP_PRINT("Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    PAP_PRINT("Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    PAP_PRINT("Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    return true;
}

void OpenGLBackend::Shutdown()
{
    // No special cleanup needed for basic GL
    PAP_PRINT("OpenGL backend shutdown");
}

void OpenGLBackend::BeginFrame()
{
    glViewport(0, 0, m_Width, m_Height);
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLBackend::EndFrame()
{
    glfwSwapBuffers(static_cast<GLFWwindow*>(m_WindowHandle));
}

void OpenGLBackend::Resize(int width, int height)
{
    m_Width = width;
    m_Height = height;
    glViewport(0, 0, width, height);
}

} // namespace pap
