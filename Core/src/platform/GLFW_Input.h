#pragma once
#include "core/Input.h"
#include <GLFW/glfw3.h>

namespace pap
{

class GLFWInput : public Input
{
public:
    explicit GLFWInput(GLFWwindow* window);
    ~GLFWInput() override = default;

protected:
    // Event hook
    void OnEventImpl(Event::Base& e) override;

    bool IsKeyPressedImpl(KeyCode keycode) const override;
    bool IsKeyReleasedImpl(KeyCode keycode) const override;

    bool IsMouseButtonPressedImpl(MouseButton button) const override;
    bool IsMouseButtonReleasedImpl(MouseButton button) const override;

    float GetMouseXImpl() const override;
    float GetMouseYImpl() const override;
    std::pair<float, float> GetMousePositionImpl() const override;

    float GetScrollXImpl() const override;
    float GetScrollYImpl() const override;
    std::pair<float, float> GetScrollOffsetImpl() const override;

private:
    GLFWwindow* m_Window = nullptr;
    float m_ScrollX = 0.0f;
    float m_ScrollY = 0.0f;
};

} // namespace pap
