#pragma once
#include <string>


namespace pap
{

// Base for GUI layers
class ImGuiWindow
{
public:
    virtual ~ImGuiWindow() = default;
    virtual void drawImGui() = 0; // pure virtual
};

} // namespace pap
