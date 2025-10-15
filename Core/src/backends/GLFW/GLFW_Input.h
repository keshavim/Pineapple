#pragma once
#include "core/Input.h"

namespace pap
{

class GLFWInput : public Input
{
public:
protected:
    // Event hook
    void OnEventImpl(Event::Base &e) override;

    bool IsKeyPressedImpl(KeyCode keycode) const override;
    bool IsKeyReleasedImpl(KeyCode keycode) const override;

    bool IsMouseButtonPressedImpl(MouseButton button) const override;
    bool IsMouseButtonReleasedImpl(MouseButton button) const override;

    float GetMouseXImpl() const override;
    float GetMouseYImpl() const override;
    std::pair<float, float> GetMousePositionImpl() const override;

private:
};

} // namespace pap
