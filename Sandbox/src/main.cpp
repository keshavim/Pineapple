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

        auto [x,y] = pap::Input::GetMousePosition();
        PAP_TRACE("{0}, {1}", x, y);
    }
};





void pap::CreateApplication()
{
    Application::PushOverlay<DemoWindow>();
    Application::PushOverlay<DBConnectionWindow>("Database Connection");
    Application::PushLayer<TriangleLayer>();
}
