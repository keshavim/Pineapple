#include "GLFW_Input.h"
#include "core/application.h"

namespace pap
{

Input* Input::s_Instance = new GLFWInput();

void GLFWInput::OnEventImpl(Event::Base& e)
{

}

bool GLFWInput::IsKeyPressedImpl(KeyCode keycode) const
{
    auto m_Window = static_cast<GLFWwindow*>(Application::GetWindow()->GetNativeHandle());
    int state = glfwGetKey(m_Window, static_cast<int>(keycode));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool GLFWInput::IsKeyReleasedImpl(KeyCode keycode) const
{
    auto m_Window = static_cast<GLFWwindow*>(Application::GetWindow()->GetNativeHandle());

    return glfwGetKey(m_Window, static_cast<int>(keycode)) == GLFW_RELEASE;
}

bool GLFWInput::IsMouseButtonPressedImpl(MouseButton button) const
{
    auto m_Window = static_cast<GLFWwindow*>(Application::GetWindow()->GetNativeHandle());

    return glfwGetMouseButton(m_Window, static_cast<int>(button)) == GLFW_PRESS;
}

bool GLFWInput::IsMouseButtonReleasedImpl(MouseButton button) const
{
    auto m_Window = static_cast<GLFWwindow*>(Application::GetWindow()->GetNativeHandle());

    return glfwGetMouseButton(m_Window, static_cast<int>(button)) == GLFW_RELEASE;
}

float GLFWInput::GetMouseXImpl() const
{
    auto m_Window = static_cast<GLFWwindow*>(Application::GetWindow()->GetNativeHandle());

    double x, y;
    glfwGetCursorPos(m_Window, &x, &y);
    return static_cast<float>(x);
}

float GLFWInput::GetMouseYImpl() const
{
    auto m_Window = static_cast<GLFWwindow*>(Application::GetWindow()->GetNativeHandle());

    double x, y;
    glfwGetCursorPos(m_Window, &x, &y);
    return static_cast<float>(y);
}

std::pair<float, float> GLFWInput::GetMousePositionImpl() const
{
    auto m_Window = static_cast<GLFWwindow*>(Application::GetWindow()->GetNativeHandle());
    
    double x, y;
    glfwGetCursorPos(m_Window, &x, &y);
    return { static_cast<float>(x), static_cast<float>(y) };
}


} // namespace pap
