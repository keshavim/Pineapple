#include <pineapple.h>

#include "DatabaseConnector.h"
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
    DatabaseConnector db;

    db.connect("MariaDbTest", "root", "jeoYfU*17g#!$B", 5);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    DBResult result = db.executeRawSQL("SELECT * FROM students.student_info;");
    std::cout << result.toString() << "\n";

    PAP_INFO("disconect start");
    db.disconnect();
    PAP_INFO("disconect end");
}
