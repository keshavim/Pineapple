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


void pap::CreateApplication()
{
    Application::PushOverlay<DemoWindow>();
    Application::PushOverlay<DBConnectionWindow>("Database Connection");
}
