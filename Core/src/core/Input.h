#pragma once
#include <utility>
#include "keycodes.h"
#include "core/event.h"

namespace pap
{

class Application; // forward declare

// ====================================================
// Input Base Class
// ====================================================
class Input
{
public:
    // Called from Application to push events into the backend
    void OnEvent(Event::Base& e) { OnEventImpl(e); }

    // Static interface (frontend)
    static bool IsKeyPressed(KeyCode keycode)   { return s_Instance->IsKeyPressedImpl(keycode); }
    static bool IsKeyReleased(KeyCode keycode)  { return s_Instance->IsKeyReleasedImpl(keycode); }

    static bool IsMouseButtonPressed(MouseButton button)  { return s_Instance->IsMouseButtonPressedImpl(button); }
    static bool IsMouseButtonReleased(MouseButton button) { return s_Instance->IsMouseButtonReleasedImpl(button); }

    static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
    static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
    static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

protected:


    // Event hook (overridable by backend)
    virtual void OnEventImpl(Event::Base& e) {}

    // Backend implementations
    virtual bool IsKeyPressedImpl(KeyCode keycode) const = 0;
    virtual bool IsKeyReleasedImpl(KeyCode keycode) const = 0;

    virtual bool IsMouseButtonPressedImpl(MouseButton button) const = 0;
    virtual bool IsMouseButtonReleasedImpl(MouseButton button) const = 0;

    virtual float GetMouseXImpl() const = 0;
    virtual float GetMouseYImpl() const = 0;
    virtual std::pair<float, float> GetMousePositionImpl() const = 0;

protected:
    static Input* s_Instance;

    friend class Application; // so Application can call OnEvent directly
};

} // namespace pap
