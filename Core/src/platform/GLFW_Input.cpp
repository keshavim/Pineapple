#include "GLFW_Input.h"

namespace pap
{

GLFWInput::GLFWInput(GLFWwindow* window)
    : m_Window(window)
{
}

void GLFWInput::OnEventImpl(Event::Base& e)
{
    PAP_EVENT_DISPATCH(Event::MouseScrolled, e, {
        m_ScrollX = e.xOffset;
        m_ScrollY = e.yOffset;
    });
}

bool GLFWInput::IsKeyPressedImpl(KeyCode keycode) const
{
    int state = glfwGetKey(m_Window, static_cast<int>(keycode));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool GLFWInput::IsKeyReleasedImpl(KeyCode keycode) const
{
    return glfwGetKey(m_Window, static_cast<int>(keycode)) == GLFW_RELEASE;
}

bool GLFWInput::IsMouseButtonPressedImpl(MouseButton button) const
{
    return glfwGetMouseButton(m_Window, static_cast<int>(button)) == GLFW_PRESS;
}

bool GLFWInput::IsMouseButtonReleasedImpl(MouseButton button) const
{
    return glfwGetMouseButton(m_Window, static_cast<int>(button)) == GLFW_RELEASE;
}

float GLFWInput::GetMouseXImpl() const
{
    double x, y;
    glfwGetCursorPos(m_Window, &x, &y);
    return static_cast<float>(x);
}

float GLFWInput::GetMouseYImpl() const
{
    double x, y;
    glfwGetCursorPos(m_Window, &x, &y);
    return static_cast<float>(y);
}

std::pair<float, float> GLFWInput::GetMousePositionImpl() const
{
    double x, y;
    glfwGetCursorPos(m_Window, &x, &y);
    return { static_cast<float>(x), static_cast<float>(y) };
}

float GLFWInput::GetScrollXImpl() const
{
    return m_ScrollX;
}

float GLFWInput::GetScrollYImpl() const
{
    return m_ScrollY;
}

std::pair<float, float> GLFWInput::GetScrollOffsetImpl() const
{
    return { m_ScrollX, m_ScrollY };
}

} // namespace pap
