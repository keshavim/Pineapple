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
    Application::pushImGuiWindow<DemoWindow>();
    Application::pushImGuiWindow<DBConnectionWindow>("Database Connection");
}
