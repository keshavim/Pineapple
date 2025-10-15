#include <pineapple.h>

#include "windows/DBConnectionWindow.h"
#include "Triangle.h"


class DemoWindow : public pap::Overlay
{
public:
    DemoWindow()
    {
    }

    void onImGuiRenderer() override
    {
        ImGui::ShowDemoWindow();

        if(pap::Input::IsKeyPressed(pap::KeyCode::A)){
            PAP_INFO("a");
        }
    }
};





void pap::CreateApplication()
{
    Application::PushOverlay<DemoWindow>();
    Application::PushOverlay<DBConnectionWindow>("Database Connection");
    Application::PushLayer<TriangleLayer>();
}
