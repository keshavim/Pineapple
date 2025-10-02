#include "pinepch.h"
#include "window.h"
#include "print.h"



namespace pap {


Window::Window(const WindowSpecifications& specs)
    : m_Specs(specs) {
}

Window::~Window() {
    Destroy();
}

void Window::Create() {


    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif
    glfwWindowHint(GLFW_RESIZABLE, m_Specs.Resizable ? GLFW_TRUE : GLFW_FALSE);

    m_Window = glfwCreateWindow(m_Specs.Width, m_Specs.Height,
         m_Specs.Title.c_str(), nullptr, nullptr);

    if (!m_Window) {
        PAP_ERROR("Failed to create GLFW window!");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_Window);
    SetVSync(m_Specs.VSync);
}

void Window::Destroy() {
    if(m_Window)
        glfwDestroyWindow(m_Window);

    m_Window = nullptr;
}

void Window::Update() {
    glfwSwapBuffers(m_Window);
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_Window);
}

void Window::SetVSync(bool enabled) {
    glfwSwapInterval(enabled ? 1 : 0);
    m_Specs.VSync = enabled;
}

std::pair<int, int> Window::GetFramebufferSize(){
    int display_w, display_h;
    glfwGetFramebufferSize(m_Window, &display_w, &display_h);
    return { display_w, display_h };
}


}
