#include "DBSchemaBrowserWindow.h"
#include "imgui.h"
#include "core/application.h"

DBSchemaBrowserWindow::DBSchemaBrowserWindow(const std::string& title)
    : m_Title(title)
{
    refreshSchemas();
}

void DBSchemaBrowserWindow::drawImGui()
{
    ImGui::Begin(m_Title.c_str());

    ImGui::Text("Schemas");
    if (m_Schemas.empty())
    {
        ImGui::TextDisabled("No schemas available.");
    }
    else
    {
        for (const auto& schema : m_Schemas)
        {
            bool selected = (m_SelectedSchema && *m_SelectedSchema == schema);
            if (ImGui::Selectable(schema.c_str(), selected))
            {
                m_SelectedSchema = schema;
                refreshTables(schema);
            }
        }
    }

    ImGui::Separator();
    ImGui::Text("Tables");
    if (!m_SelectedSchema)
    {
        ImGui::TextDisabled("Select a schema first.");
    }
    else if (m_Tables.empty())
    {
        ImGui::TextDisabled("No tables in this schema.");
    }
    else
    {
        for (const auto& table : m_Tables)
        {
            ImGui::BulletText("%s", table.name.c_str());
        }
    }

    ImGui::End();
}

void DBSchemaBrowserWindow::refreshSchemas()
{
    auto& mgr = pap::Application::Get().getDBManager();
    auto res = mgr.listSchemas();
    if (res)
    {
        m_Schemas = *res;
    }
    else
    {
        m_Schemas.clear();
    }
}

void DBSchemaBrowserWindow::refreshTables(const std::string& schema)
{
    auto& mgr = pap::Application::Get().getDBManager();
    auto res = mgr.listTables(schema);
    if (res)
    {
        m_Tables = *res;
    }
    else
    {
        m_Tables.clear();
    }
}
