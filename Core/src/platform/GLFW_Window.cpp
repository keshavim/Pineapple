#include "core/Input.h"
#include "pinepch.h"
#include "platform/GLFW_Input.h"
#include "GLFW_Window.h"

namespace pap
{

GLFWWindow::GLFWWindow(const WindowSpecifications &specs)
{
    m_Data.Title = specs.Title;
    m_Data.Width = specs.Width;
    m_Data.Height = specs.Height;
    m_Data.VSync = specs.VSync;
    m_Data.Resizable = specs.Resizable;
    m_Data.rendererbackend = specs.rendererbackend;
}

GLFWWindow::~GLFWWindow()
{
    Destroy();
}

void GLFWWindow::Create()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, m_Data.Resizable ? GLFW_TRUE : GLFW_FALSE);

    m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
    if (!m_Window)
    {
        PAP_ERROR("Failed to create GLFW window!");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_Window);

    RendererInitInfo info;
    info.windowHandle = m_Window;
    auto [w, h] = GetFramebufferSize();
    info.width = w;
    info.height = h;
    info.backend = m_Data.rendererbackend;
    Renderer::Init(info);

    GLFWInput input(m_Window);

    SetVSync(m_Data.VSync);
    glfwSetWindowUserPointer(m_Window, &m_Data);

    // -------------------------
    // Callbacks
    // -------------------------
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
        auto &data = *(Data *)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;

        Event::WindowResized e(width, height);
        if (data.EventCallback) data.EventCallback(e);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
        auto &data = *(Data *)glfwGetWindowUserPointer(window);
        Event::WindowClosed e;
        if (data.EventCallback) data.EventCallback(e);
    });

    glfwSetWindowFocusCallback(m_Window, [](GLFWwindow *window, int focused) {
        auto &data = *(Data *)glfwGetWindowUserPointer(window);
        Event::WindowFocused e(focused != 0);
        if (data.EventCallback) data.EventCallback(e);
    });

    glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow *window, int iconified) {
        auto &data = *(Data *)glfwGetWindowUserPointer(window);
        Event::WindowMinimized e(iconified != 0);
        if (data.EventCallback) data.EventCallback(e);
    });

    glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow *window, int maximized) {
        auto &data = *(Data *)glfwGetWindowUserPointer(window);
        Event::WindowMaximized e(maximized != 0);
        if (data.EventCallback) data.EventCallback(e);
    });

    glfwSetWindowContentScaleCallback(m_Window, [](GLFWwindow *window, float xScale, float yScale) {
        auto &data = *(Data *)glfwGetWindowUserPointer(window);
        Event::WindowContentScaleChanged e(xScale, yScale);
        if (data.EventCallback) data.EventCallback(e);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto &data = *(Data *)glfwGetWindowUserPointer(window);
        if (action == GLFW_PRESS)
        {
            Event::KeyPressed e(static_cast<KeyCode>(key), false);
            if (data.EventCallback) data.EventCallback(e);
        }
        else if (action == GLFW_REPEAT)
        {
            Event::KeyPressed e(static_cast<KeyCode>(key), true);
            if (data.EventCallback) data.EventCallback(e);
        }
        else if (action == GLFW_RELEASE)
        {
            Event::KeyReleased e(static_cast<KeyCode>(key));
            if (data.EventCallback) data.EventCallback(e);
        }
    });

    glfwSetCharCallback(m_Window, [](GLFWwindow *window, uint32_t c) {
        auto &data = *(Data *)glfwGetWindowUserPointer(window);
        Event::CharTyped e(c);
        if (data.EventCallback) data.EventCallback(e);
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
        auto &data = *(Data *)glfwGetWindowUserPointer(window);
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        if (action == GLFW_PRESS)
        {
            Event::MouseButtonPressed e(static_cast<MouseButton>(button), x, y);
            if (data.EventCallback) data.EventCallback(e);
        }
        else if (action == GLFW_RELEASE)
        {
            Event::MouseButtonReleased e(static_cast<MouseButton>(button), x, y);
            if (data.EventCallback) data.EventCallback(e);
        }
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double x, double y) {
        auto &data = *(Data *)glfwGetWindowUserPointer(window);
        Event::MouseMoved e(x, y);
        if (data.EventCallback) data.EventCallback(e);
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
        auto &data = *(Data *)glfwGetWindowUserPointer(window);

        Event::MouseScrolled e(xOffset, yOffset);
        if (data.EventCallback) data.EventCallback(e);
    });
}

void GLFWWindow::Destroy()
{
    if (m_Window)
        glfwDestroyWindow(m_Window);

    m_Window = nullptr;
}

void GLFWWindow::Update()
{
    glfwSwapBuffers(m_Window);
}

bool GLFWWindow::ShouldClose() const
{
    return glfwWindowShouldClose(m_Window);
}

void GLFWWindow::SetVSync(bool enabled)
{
    glfwSwapInterval(enabled ? 1 : 0);
    m_Data.VSync = enabled;
}

std::pair<int, int> GLFWWindow::GetFramebufferSize()
{
    int display_w, display_h;
    glfwGetFramebufferSize(m_Window, &display_w, &display_h);
    return {display_w, display_h};
}

std::pair<int, int> GLFWWindow::GetWindowSize() const
{
    return {m_Data.Width, m_Data.Height};
}

} // namespace pap
