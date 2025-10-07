#include "Table.h"

namespace pap
{


namespace widgets
{

Table::Table(const std::string &id, const std::vector<std::string> &columnNames) : m_ID(id), m_ColumnNames(columnNames)
{
}

void Table::setColumns(const std::vector<std::string> &columnNames)
{
    m_ColumnNames = columnNames;
}

void Table::setData(const std::vector<std::vector<std::string>> &rows)
{
    m_Rows = rows;
}

// Translate our TableFlags to ImGuiTableFlags
ImGuiTableFlags Table::getImGuiFlags() const
{
    ImGuiTableFlags flags = ImGuiTableFlags_None;

    if ((m_Flags & Table_Borders) != 0)
        flags |= ImGuiTableFlags_Borders;
    if ((m_Flags & Table_RowBg) != 0)
        flags |= ImGuiTableFlags_RowBg;
    if ((m_Flags & Table_Resizable) != 0)
        flags |= ImGuiTableFlags_Resizable;
    if ((m_Flags & Table_Reorderable) != 0)
        flags |= ImGuiTableFlags_Reorderable;
    if ((m_Flags & Table_Hideable) != 0)
        flags |= ImGuiTableFlags_Hideable;
    if ((m_Flags & Table_Sortable) != 0)
        flags |= ImGuiTableFlags_Sortable;
    if ((m_Flags & Table_ScrollX) != 0)
        flags |= ImGuiTableFlags_ScrollX;
    if ((m_Flags & Table_ScrollY) != 0)
        flags |= ImGuiTableFlags_ScrollY;

    return flags;
}
void Table::draw()
{
    if (m_ColumnNames.empty())
    {
        ImGui::TextUnformatted("No columns defined for table.");
        return;
    }

    // -------------------- Foldable --------------------
    bool drawTable = true;

    if ((m_Flags & Table_Foldable) != 0)
    {
        ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap;
        drawTable = ImGui::TreeNodeEx(m_ID.c_str(), treeFlags, "%s", m_ID.c_str());

        if (!drawTable)
            return; // folded, skip table
    }

    // -------------------- Table --------------------
    ImGuiTableFlags imguiFlags = getImGuiFlags();
    if (ImGui::BeginTable(m_ID.c_str(), static_cast<int>(m_ColumnNames.size()), imguiFlags))
    {
        setupColumns();   // auto-resize or stretch
        drawHeaders();    // header row
        drawRows();       // table data
        ImGui::EndTable();
    }

    // -------------------- TreePop --------------------
    if ((m_Flags & Table_Foldable) != 0)
        ImGui::TreePop();
}
// ------------------------- Helper Functions -------------------------

// -------------------- Column Setup --------------------
void Table::setupColumns()
{
    if (m_ColumnNames.empty())
        return;

    for (int c = 0; c < static_cast<int>(m_ColumnNames.size()); ++c)
    {
        // Default to stretch
        ImGuiTableColumnFlags colFlags = ImGuiTableColumnFlags_WidthStretch;

        // Auto-resize: fix width based on max cell width
        if ((m_Flags & Table_AutoResize) != 0)
        {
            float padding = 10.0f;
            float maxWidth = ImGui::CalcTextSize(m_ColumnNames[c].c_str()).x + padding;

            for (const auto& row : m_Rows)
            {
                if (c < static_cast<int>(row.size()))
                {
                    float cellWidth = ImGui::CalcTextSize(row[c].c_str()).x + padding;
                    if (cellWidth > maxWidth)
                        maxWidth = cellWidth;
                }
            }

            colFlags = ImGuiTableColumnFlags_WidthFixed;
            ImGui::TableSetupColumn(m_ColumnNames[c].c_str(), colFlags, maxWidth);
            continue;
        }

        ImGui::TableSetupColumn(m_ColumnNames[c].c_str(), colFlags);
    }
}

// -------------------- Fold button / title --------------------
// Fixed: Use TreeNodeEx to get proper folding arrow like ImGui demo
bool Table::drawFoldButton()
{
    if ((m_Flags & Table_Foldable) == 0)
        return true; // always draw table

    ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap;

    // TreeNodeEx returns true if expanded
    bool expanded = ImGui::TreeNodeEx(m_ID.c_str(), treeFlags, "%s", m_ID.c_str());
    if (!expanded)
        return false; // folded, skip table

    return true; // table should be drawn
}

// -------------------- Header --------------------
void Table::drawHeaders()
{
    ImGui::TableHeadersRow(); // draw headers automatically
}

// -------------------- Rows --------------------
void Table::drawRows()
{
    if (m_Rows.empty())
    {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TextUnformatted("No data to display.");
        return;
    }

    for (const auto& row : m_Rows)
    {
        ImGui::TableNextRow();
        for (int c = 0; c < static_cast<int>(m_ColumnNames.size()); ++c)
        {
            ImGui::TableSetColumnIndex(c);
            if (c < static_cast<int>(row.size()))
                ImGui::TextUnformatted(row[c].c_str());
            else
                ImGui::TextUnformatted("");
        }
    }
}


} // namespace widgets
} // namespace pap
