#include <dbc/DBManager.h>
#include <pineapple.h>

#include "imgui.h"


class DemoWindow : public pap::ImGuiWindow
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
    LayerManager::pushGuiWindow<DemoWindow>();
}
