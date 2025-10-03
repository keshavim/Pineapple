#pragma once
#include "ImGuiLayer.h"
#include <GLFW/glfw3.h>


namespace pap
{

class ImGuiDockSpaceLayer : public ImGuiLayer
{
public:
    ImGuiDockSpaceLayer();
    ~ImGuiDockSpaceLayer() override;

    void drawImGui() override;
};

} // namespace pap
