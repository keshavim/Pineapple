#include "OpenGLBackend.h"
#include "pinepch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>



void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                      GLsizei length, GLchar const *message,
                      void const *user_param) {
  if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
    return;

  auto const src_str = [source]() {
    switch (source) {
    case GL_DEBUG_SOURCE_API:
      return "API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      return "WINDOW SYSTEM";
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      return "SHADER COMPILER";
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      return "THIRD PARTY";
    case GL_DEBUG_SOURCE_APPLICATION:
      return "APPLICATION";
    case GL_DEBUG_SOURCE_OTHER:
      return "OTHER";
    default:
      return "UNKNOWN SOURCE";
    }
  }();

  auto const type_str = [type]() {
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      return "ERROR";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      return "DEPRECATED_BEHAVIOR";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      return "UNDEFINED_BEHAVIOR";
    case GL_DEBUG_TYPE_PORTABILITY:
      return "PORTABILITY";
    case GL_DEBUG_TYPE_PERFORMANCE:
      return "PERFORMANCE";
    case GL_DEBUG_TYPE_MARKER:
      return "MARKER";
    case GL_DEBUG_TYPE_OTHER:
      return "OTHER";
    default:
      return "UNKNOWN TYPE";
    }
  }();

  auto const severity_str = [severity]() {
    switch (severity) {
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      return "NOTIFICATION";
    case GL_DEBUG_SEVERITY_LOW:
      return "LOW";
    case GL_DEBUG_SEVERITY_MEDIUM:
      return "MEDIUM";
    case GL_DEBUG_SEVERITY_HIGH:
      return "HIGH";
    default:
      return "UNKNOWN SEVERITY";
    }
  }();
  PAP_ERROR("{}, {}, {}, {}: {}", src_str, type_str, severity_str, id,  message);
}




namespace pap
{

bool OpenGLBackend::Init(const RendererInitInfo& info)
{
    m_WindowHandle = info.windowHandle;
    m_Width = info.width;
    m_Height = info.height;

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    assert(status && "Failed glad load");

    glViewport(0, 0, m_Width, m_Height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(message_callback, nullptr);

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
