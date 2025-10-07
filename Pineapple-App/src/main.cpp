#include <dbc/DBManager.h>
#include <pineapple.h>

#include "imgui.h"
#include "windows/DBWindow.h"


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
    Application::pushGuiWindow<DemoWindow>();
    Application::pushGuiWindow<DBWindow>("Database Table");
}
