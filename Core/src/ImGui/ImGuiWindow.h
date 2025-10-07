#pragma once
#include <string>
#include "core/event.h"


namespace pap
{

// Base for GUI layers
class ImGuiWindow
{
public:
    virtual ~ImGuiWindow() = default;
    virtual void drawImGui() = 0;
    virtual bool wantsCapture() const { return true; }
    virtual void onEvent(Event::Base& e) {}
};

} // namespace pap
