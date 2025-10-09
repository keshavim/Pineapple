#include "windows/DBConnectionWindow.h"
#include <dbc/Manager.h>
#include <pineapple.h>


class DemoWindow : public pap::Layer
{
public:
    DemoWindow()
    {
    }

    void onRender() override
    {
        ImGui::ShowDemoWindow();
    }
};


void pap::InitApplication()
{
    Application::pushOverlay<DemoWindow>();
    Application::pushOverlay<DBConnectionWindow>("Database Connection");
}
