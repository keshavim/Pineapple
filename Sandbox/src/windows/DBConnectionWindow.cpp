#include "DBConnectionWindow.h"
#include "DBSchemaBrowserWindow.h"
#include "core/application.h"
#include "imgui.h"

DBConnectionWindow::DBConnectionWindow(const std::string &title) : m_Title(title)
{
}

void DBConnectionWindow::onRender()
{
    ImGui::Begin(m_Title.c_str());

    ImGui::Text("New Connection");
    ImGui::InputText("URI", m_Uri, IM_ARRAYSIZE(m_Uri));
    ImGui::InputText("User", m_User, IM_ARRAYSIZE(m_User));
    ImGui::InputText("Password", m_Password, IM_ARRAYSIZE(m_Password), ImGuiInputTextFlags_Password);

    const char *drivers[] = {"MariaDB"};
    int current = static_cast<int>(m_SelectedDriver);
    if (ImGui::Combo("Driver", &current, drivers, IM_ARRAYSIZE(drivers)))
        m_SelectedDriver = static_cast<pap::db::Driver>(current);

    if (ImGui::Button("Connect"))
    {
        pap::db::ConnectInfo info{m_SelectedDriver, m_Uri, m_User, m_Password};
        auto key = makeKey(info);

        // Only connect if not already connected
        if (!m_ConnectionWindows.contains(key))
        {
            auto res = connectNew();
            if (!res)
            {
                ImGui::OpenPopup("Connection Error");
            }
            else
            {
                // Push overlay for this connection
                size_t idx = pap::Application::PushOverlay<DBSchemaBrowserWindow>(key);
                m_ConnectionWindows[key] = idx;
            }
        }
    }

    if (ImGui::BeginPopupModal("Connection Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Failed to connect.");
        if (ImGui::Button("OK"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }

    ImGui::Separator();
    ImGui::Text("Saved Connections");

    auto &mgr = pap::Application::GetDBManager();
    const auto &connections = mgr.getConnections();

    if (connections.empty())
    {
        ImGui::TextDisabled("No saved connections.");
    }
    else
    {
        for (const auto &c : connections)
        {
            auto key = makeKey(c);
            if (ImGui::Button(key.c_str()))
            {
                auto it = m_ConnectionWindows.find(key);

                if (it != m_ConnectionWindows.end())
                {
                    size_t idx = it->second;
                    auto state = pap::Application::GetLayerState(idx);

                    if (state == pap::LayerState::Deleted)
                    {
                        // Revive the window instead of creating a new one
                        pap::Application::SetLayerState(idx, pap::LayerState::Active);
                    }
                    // Already active, do nothing
                }
                else
                {
                    // No existing window, create a new one
                    auto res = reconnect(c);
                    if (!res)
                    {
                        ImGui::OpenPopup("Connection Error");
                    }
                    else
                    {
                        size_t idx = pap::Application::PushOverlay<DBSchemaBrowserWindow>(key);
                        m_ConnectionWindows[key] = idx;
                    }
                }
            }
        }
    }

    ImGui::End();
}

pap::db::Result<void> DBConnectionWindow::connectNew()
{
    pap::db::ConnectInfo info{m_SelectedDriver, m_Uri, m_User, m_Password};
    return pap::Application::GetDBManager().connect(info);
}

pap::db::Result<void> DBConnectionWindow::reconnect(const pap::db::ConnectInfo &info)
{
    return pap::Application::GetDBManager().connect(info);
}
