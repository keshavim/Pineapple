#include "DBTableViewerWindow.h"
#include "core/application.h"
#include <imgui.h>


void DBTableViewerWindow::onImGuiRenderer()
{
    // In drawImGui:
if (!m_Open) {
    setState(pap::LayerState::Deleted);
    return;
}

// Flags for full, resizable, closable, and tabbed window
ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse |
                         ImGuiWindowFlags_MenuBar |
                         ImGuiWindowFlags_NoSavedSettings;

// Pass &m_Open so user can close the window with [X]
if (ImGui::Begin(m_Title.c_str(), &m_Open, flags))
{
    auto &dbManager = pap::Application::GetDBManager();

    // Query table data once
    if (!m_Queried)
    {
        auto res = dbManager.executeQuery(std::format("SELECT * FROM {}.{};", m_Schema, m_Title));
        if (res)
            m_TableData.emplace(std::move(*res));
        m_Queried = true;
    }

    if (!m_TableData)
    {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "Failed to fetch table data");
    }
    else
    {
        const auto &data = *m_TableData;

        if (ImGui::BeginTable("FullTable", data.getColumnCount(),
                              ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
                              ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable |
                              ImGuiTableFlags_Hideable))
        {
            // Headers
            for (size_t c = 0; c < data.getColumnCount(); ++c)
            {
                auto colNameRes = data.getColumnName(c);
                ImGui::TableSetupColumn(colNameRes ? colNameRes->c_str() : "N/A");
            }
            ImGui::TableHeadersRow();

            // Rows
            for (size_t r = 0; r < data.getRowCount(); ++r)
            {
                ImGui::TableNextRow();
                auto rowRes = data.getRow(r);
                if (!rowRes) continue;

                for (size_t c = 0; c < rowRes->size(); ++c)
                {
                    ImGui::TableSetColumnIndex(c);
                    ImGui::TextUnformatted((*rowRes)[c].c_str());
                }
            }

            ImGui::EndTable();
        }
    }

    ImGui::End();
}

}
