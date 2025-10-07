#pragma once
#include "core/event.h"
#include "imgui.h"

namespace pap
{


namespace widgets
{

// Base class for all widgets
class Widget
{
public:
    virtual ~Widget() = default;

    // Draw the widget
    virtual void draw() = 0;

    // Optional: update internal state
    virtual void update()
    {
    }

    // Optional: handle events
    virtual void onEvent(Event::Base &e)
    {
    }

    // Some widgets may want ImGui to capture input
    virtual bool wantsCapture() const
    {
        return true;
    }
};
} // namespace widgets
} // namespace pap
