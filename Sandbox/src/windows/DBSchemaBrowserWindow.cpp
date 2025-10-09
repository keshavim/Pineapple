#include "DBSchemaBrowserWindow.h"
#include "DBTableViewerWindow.h"
#include "core/application.h"
#include "imgui.h"

DBSchemaBrowserWindow::DBSchemaBrowserWindow(const std::string &title) : m_Title(title)
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
        for (const auto &schema : m_Schemas)
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
        auto &dbManager = pap::Application::Get().getDBManager();

        for (const auto &table : m_Tables)
        {
            // Each table becomes a collapsible header
            if (ImGui::CollapsingHeader(table.name.c_str()))
            {
                // Fetch table info
                auto tinfoResult = dbManager.getTableInfo(*m_SelectedSchema, table.name);
                if (tinfoResult)
                {
                    const pap::db::TableInfo &tinfo = *tinfoResult;

                    ImGui::Text("Columns (%zu):", tinfo.columns.size());
                    for (const auto &col : tinfo.columns)
                    {
                        ImGui::BulletText("%s : %s%s%s",
                                          col.name.c_str(),
                                          col.type.c_str(),
                                          col.isPrimaryKey ? " [PK]" : "",
                                          col.isNullable ? " [NULL]" : " [NOT NULL]");
                    }

                    // Button to open full table viewer
                    ImGui::Spacing();
                    if (ImGui::Button(("View Table: " + table.name).c_str()))
                    {
                        // Open a new DBTableViewerWindow for this table
                        pap::Application::pushImGuiWindow<DBTableViewerWindow>(table.name, *m_SelectedSchema);
                    }
                }
                else
                {
                    ImGui::TextColored(ImVec4(1, 0, 0, 1), "Failed to fetch table info");
                }
            }
        }
    }

    ImGui::End();
}

void DBSchemaBrowserWindow::refreshSchemas()
{
    auto &mgr = pap::Application::Get().getDBManager();
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

void DBSchemaBrowserWindow::refreshTables(const std::string &schema)
{
    auto &mgr = pap::Application::Get().getDBManager();
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
