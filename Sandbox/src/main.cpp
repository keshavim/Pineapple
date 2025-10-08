#include "windows/DBConnectionWindow.h"
#include <dbc/DBManager.h>
#include <pineapple.h>


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
    Application::pushGuiWindow<DBConnectionWindow>("Database Connection");
}
