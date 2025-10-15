#include "pinepch.h"

#include "OpenGLContext.h"
#include "core/core.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


void message_callback(GLenum source,
                      GLenum type,
                      GLuint id,
                      GLenum severity,
                      GLsizei length,
                      GLchar const *message,
                      void const *user_param)
{
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        return;

    auto const src_str = [source]() {
        switch (source)
        {
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
        switch (type)
        {
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
        switch (severity)
        {
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
    PAP_ERROR("{}, {}, {}, {}: {}", src_str, type_str, severity_str, id, message);
}


namespace pap
{
OpenGLContext::OpenGLContext(GLFWwindow *windowhandle) : m_windowhandle(windowhandle)
{
    assert(m_windowhandle && "OpenGLContext windowhandle is null");
}
void OpenGLContext::Init()
{


    glfwMakeContextCurrent(m_windowhandle);
    int s = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    assert(s && "glad loadgl failed");


    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glDebugMessageCallback(message_callback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

        PAP_INFO("OpenGL debug output enabled");
    }

    PAP_INFO("OpenGL Version: {}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
    PAP_INFO("Renderer: {}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
    PAP_INFO("Vendor: {}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int width, height;
    glfwGetFramebufferSize(m_windowhandle, &width, &height);
    glViewport(0, 0, width, height);
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_windowhandle);
}


} // namespace pap
