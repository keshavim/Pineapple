#include <pineapple.h>

#include "imgui.h"


class DemoWindow : public pap::ImGuiLayer
{
public:
    DemoWindow()
    {
    }

    void drawImGui() override
    {
        ImGui::ShowDemoWindow();
    }
};


void pap::InitApplication()
{
    LayerManager::pushGuiLayer<DemoWindow>();
}
