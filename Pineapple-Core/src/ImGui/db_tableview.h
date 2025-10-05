// db_result_view_component.h
#ifndef DB_RESULT_VIEW_COMPONENT_H
#define DB_RESULT_VIEW_COMPONENT_H

#include "dbc/db_result.h"
#include <imgui.h>

namespace pap {
class DBResultViewComponent {
public:
    DBResultViewComponent(const DBResult& result)
        : m_Result(result) {}

    void draw() {
        if (m_Result.getRowCount() == 0) {
            ImGui::TextUnformatted("No results to display.");
            return;
        }

        const auto cols = m_Result.getColumnCount();
        const auto& colNames = m_Result.getColumnNames();

        if (ImGui::BeginTable("DBResultTable", static_cast<int>(cols), ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            // Header
            ImGui::TableHeadersRow();
            for (const auto& name : colNames) {
                ImGui::TableSetColumnIndex(static_cast<int>(&name - &colNames[0]));
                ImGui::TextUnformatted(name.c_str());
            }

            // Rows
            for (size_t r = 0; r < m_Result.getRowCount(); ++r) {
                ImGui::TableNextRow();
                const auto row = m_Result.getRow(r);
                for (size_t c = 0; c < row.size(); ++c) {
                    ImGui::TableSetColumnIndex(static_cast<int>(c));
                    ImGui::TextUnformatted(row[c].c_str());
                }
            }

            ImGui::EndTable();
        }
    }

private:
    DBResult m_Result;
};

}
#endif
