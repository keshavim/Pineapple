#include "DBConnectionWindow.h"
#include "DBSchemaBrowserWindow.h"
#include "imgui.h"
#include "core/application.h"

DBConnectionWindow::DBConnectionWindow(const std::string& title)
    : m_Title(title)
{
}

void DBConnectionWindow::drawImGui()
{
    ImGui::Begin(m_Title.c_str());

    ImGui::Text("New Connection");
    ImGui::InputText("URI", m_Uri, IM_ARRAYSIZE(m_Uri));
    ImGui::InputText("User", m_User, IM_ARRAYSIZE(m_User));
    ImGui::InputText("Password", m_Password, IM_ARRAYSIZE(m_Password), ImGuiInputTextFlags_Password);

    // Driver dropdown (only MariaDB for now)
    const char* drivers[] = { "MariaDB" };
    int current = static_cast<int>(m_SelectedDriver);
    if (ImGui::Combo("Driver", &current, drivers, IM_ARRAYSIZE(drivers)))
    {
        m_SelectedDriver = static_cast<pap::DBDriver>(current);
    }

    if (ImGui::Button("Connect"))
    {
        connectNew();
    }

    ImGui::Separator();
    ImGui::Text("Saved Connections");

    auto& mgr = pap::Application::Get().getDBManager();
    const auto& connections = mgr.getConnections();

    if (connections.empty())
    {
        ImGui::TextDisabled("No saved connections.");
    }
    else
    {
        for (const auto& c : connections)
        {
            std::string label = c.user + "@" + c.uri;
            if (ImGui::Button(label.c_str()))
            {
                reconnect(c);
            }
        }
    }

    ImGui::End();
}

void DBConnectionWindow::connectNew()
{
    pap::ConnectInfo info{
        m_SelectedDriver,
        m_Uri,
        m_User,
        m_Password,
    };

    auto& mgr = pap::Application::Get().getDBManager();
    auto res = mgr.connect(info);
    if (!res)
    {
        // Simple ImGui error popup
        ImGui::OpenPopup("Connection Error");
    }

    if (ImGui::BeginPopupModal("Connection Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Failed to connect:\n%s", res.error().c_str());
        if (ImGui::Button("OK"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }

    if (res)
    {
        // Open a schema browser window for this connection
        pap::Application::pushGuiWindow<DBSchemaBrowserWindow>("Schema Browser");
    }
}

void DBConnectionWindow::reconnect(const pap::ConnectInfo& info)
{
    auto& mgr = pap::Application::Get().getDBManager();
    auto res = mgr.connect(info);
    if (!res)
    {
        ImGui::OpenPopup("Connection Error");
    }

    if (ImGui::BeginPopupModal("Connection Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Failed to connect:\n%s", res.error().c_str());
        if (ImGui::Button("OK"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }

    if (res)
    {
        pap::Application::pushGuiWindow<DBSchemaBrowserWindow>("Schema Browser");
    }
}
