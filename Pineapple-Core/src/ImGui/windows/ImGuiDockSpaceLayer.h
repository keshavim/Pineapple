#pragma once
#include "../ImGuiWindow.h"
#include <GLFW/glfw3.h>


namespace pap
{

class ImGuiDockSpace : public ImGuiWindow
{
public:
    ImGuiDockSpace();
    ~ImGuiDockSpace() override;

    void drawImGui() override;
};

} // namespace pap
