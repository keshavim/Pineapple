#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include "keycodes.h"

namespace pap
{


enum class EventType
{
    None = 0,
    // Key
    KeyPressed,
    KeyReleased,
    CharInput,
    // Mouse
    MouseMoved,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseScrolled,
    // Window
    WindowResized,
    WindowClosed,
    WindowFocused,
    WindowMinimized,
    WindowMaximized,
    WindowContentScaleChanged
};

namespace Event
{

// --------------------
// Base Event Interface
// --------------------
class Base
{
public:
    virtual ~Base() = default;

    virtual EventType getType() const = 0;
    virtual std::string toString() const = 0;

    bool handled = false;
};

// --------------------
// Key Events
// --------------------
class Key : public Base
{
public:
    KeyCode key;
    Key(KeyCode key) : key(key)
    {
    }
};

class KeyPressed : public Key
{
public:
    bool repeat;
    KeyPressed(KeyCode key, bool repeat = false) : Key(key), repeat(repeat)
    {
    }
    static EventType StaticType()
    {
        return EventType::KeyPressed;
    }
    EventType getType() const override
    {
        return StaticType();
    }
    std::string toString() const override
    {
        return "KeyPressed: " + std::to_string((int)key) + (repeat ? " (repeat)" : "");
    }
};

class KeyReleased : public Key
{
public:
    KeyReleased(KeyCode key) : Key(key)
    {
    }
    static EventType StaticType()
    {
        return EventType::KeyReleased;
    }
    EventType getType() const override
    {
        return StaticType();
    }
    std::string toString() const override
    {
        return "KeyReleased: " + std::to_string((int)key);
    }
};

class CharTyped : public Base
{
public:
    uint32_t character;
    CharTyped(uint32_t character) : character(character)
    {
    }
    static EventType StaticType()
    {
        return EventType::CharInput;
    }
    EventType getType() const override
    {
        return StaticType();
    }
    std::string toString() const override
    {
        return "CharInput: " + std::to_string((unsigned int)character);
    }
};

// --------------------
// Mouse Events
// --------------------
class Mouse : public Base
{
public:
    double x, y;
    Mouse(double x = 0, double y = 0) : x(x), y(y)
    {
    }
};

class MouseMoved : public Mouse
{
public:
    MouseMoved(double x, double y) : Mouse(x, y)
    {
    }
    static EventType StaticType()
    {
        return EventType::MouseMoved;
    }
    EventType getType() const override
    {
        return StaticType();
    }
    std::string toString() const override
    {
        return "MouseMoved: (" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

class MouseButtonPressed : public Mouse
{
public:
    MouseButton button;
    MouseButtonPressed(MouseButton button, double x, double y) : Mouse(x, y), button(button)
    {
    }
    static EventType StaticType()
    {
        return EventType::MouseButtonPressed;
    }
    EventType getType() const override
    {
        return StaticType();
    }
    std::string toString() const override
    {
        return "MouseButtonPressed: " + std::to_string((int)button) + " at (" + std::to_string(x) + ", " +
               std::to_string(y) + ")";
    }
};

class MouseButtonReleased : public Mouse
{
public:
    MouseButton button;
    MouseButtonReleased(MouseButton button, double x, double y) : Mouse(x, y), button(button)
    {
    }
    static EventType StaticType()
    {
        return EventType::MouseButtonReleased;
    }
    EventType getType() const override
    {
        return StaticType();
    }
    std::string toString() const override
    {
        return "MouseButtonReleased: " + std::to_string((int)button) + " at (" + std::to_string(x) + ", " +
               std::to_string(y) + ")";
    }
};

class MouseScrolled : public Mouse
{
public:
    double xOffset, yOffset;
    MouseScrolled(double xOffset, double yOffset, double x = 0, double y = 0)
        : Mouse(x, y), xOffset(xOffset), yOffset(yOffset)
    {
    }
    static EventType StaticType()
    {
        return EventType::MouseScrolled;
    }
    EventType getType() const override
    {
        return StaticType();
    }
    std::string toString() const override
    {
        return "MouseScrolled: (" + std::to_string(xOffset) + ", " + std::to_string(yOffset) + ")";
    }
};

// --------------------
// Window Events
// --------------------
class Window : public Base
{
};

class WindowResized : public Window
{
public:
    int width, height;
    WindowResized(int width, int height) : width(width), height(height)
    {
    }
    static EventType StaticType()
    {
        return EventType::WindowResized;
    }
    EventType getType() const override
    {
        return StaticType();
    }
    std::string toString() const override
    {
        return "WindowResized: " + std::to_string(width) + "x" + std::to_string(height);
    }
};

class WindowClosed : public Window
{
public:
    WindowClosed() = default;
    static EventType StaticType()
    {
        return EventType::WindowClosed;
    }
    EventType getType() const override
    {
        return StaticType();
    }
    std::string toString() const override
    {
        return "WindowClosed";
    }
};

class WindowFocused : public Window
{
public:
    bool focused;
    WindowFocused(bool focused) : focused(focused)
    {
    }
    static EventType StaticType()
    {
        return EventType::WindowFocused;
    }
    EventType getType() const override
    {
        return StaticType();
    }
    std::string toString() const override
    {
        return std::string("WindowFocused: ") + (focused ? "true" : "false");
    }
};

class WindowMinimized : public Window
{
public:
    bool minimized;
    WindowMinimized(bool minimized) : minimized(minimized)
    {
    }
    static EventType StaticType()
    {
        return EventType::WindowMinimized;
    }
    EventType getType() const override
    {
        return StaticType();
    }
    std::string toString() const override
    {
        return std::string("WindowIconified: ") + (minimized ? "true" : "false");
    }
};

class WindowMaximized : public Window
{
public:
    bool maximized;
    WindowMaximized(bool maximized) : maximized(maximized)
    {
    }
    static EventType StaticType()
    {
        return EventType::WindowMaximized;
    }
    EventType getType() const override
    {
        return StaticType();
    }
    std::string toString() const override
    {
        return std::string("WindowMaximized: ") + (maximized ? "true" : "false");
    }
};

class WindowContentScaleChanged : public Window
{
public:
    float xScale, yScale;
    WindowContentScaleChanged(float xScale, float yScale) : xScale(xScale), yScale(yScale)
    {
    }
    static EventType StaticType()
    {
        return EventType::WindowContentScaleChanged;
    }
    EventType getType() const override
    {
        return StaticType();
    }
    std::string toString() const override
    {
        return "WindowContentScaleChanged: (" + std::to_string(xScale) + ", " + std::to_string(yScale) + ")";
    }
};


// Type-safe dispatcher function
template <typename T>
void dispatch(Event::Base &e, const std::function<void(T &)> &func)
{
    if (e.getType() == T::StaticType())
    {
        func(static_cast<T &>(e));
    }
}

} // namespace Event
} // namespace pap


// Macro to simplify event dispatch
#define PAP_EVENT_DISPATCH(EventType, EventVar, ...) \
    Event::dispatch<EventType>(EventVar, [&](EventType& e) { __VA_ARGS__; })
