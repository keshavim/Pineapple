#pragma once
#include "Wiget.h"

namespace pap
{


// Custom table flags
enum TableFlags : uint32_t
{
    Table_None        = 0,
    Table_Resizable   = 1 << 0,  // columns can be resized
    Table_Reorderable = 1 << 1,  // columns can be reordered
    Table_Hideable    = 1 << 2,  // columns can be hidden
    Table_Sortable    = 1 << 3,  // columns can be sorted
    Table_RowBg       = 1 << 4,  // alternating row colors
    Table_Borders     = 1 << 5,  // draw borders
    Table_ScrollX     = 1 << 6,  // horizontal scrolling
    Table_ScrollY     = 1 << 7,  // vertical scrolling

    // Custom flags not in ImGui
    Table_Foldable    = 1 << 16, // table can be folded/collapsed
    Table_AutoResize  = 1 << 17  // automatically resize columns to fit content
};

inline TableFlags operator|(TableFlags a, TableFlags b) { return static_cast<TableFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b)); }
inline TableFlags operator&(TableFlags a, TableFlags b) { return static_cast<TableFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b)); }




namespace widgets
{


class Table : public Widget
{
public:
    Table(const std::string& id, const std::vector<std::string>& columnNames = {});

    void setColumns(const std::vector<std::string>& columnNames);
    void setData(const std::vector<std::vector<std::string>>& rows);

    void setFlags(TableFlags flags) { m_Flags = flags; }
    TableFlags getFlags() const { return m_Flags; }

    void draw() override;


private:
    std::string m_ID;
    std::vector<std::string> m_ColumnNames;
    std::vector<std::vector<std::string>> m_Rows;

    TableFlags m_Flags = Table_None;
    bool m_IsFolded = false;

    ImGuiTableFlags getImGuiFlags() const; // translate custom flags to ImGuiTableFlags

private:
    bool drawFoldButton();
    void setupColumns();
    void drawHeaders();
    void drawRows();
};

} // namespace widgets
} // namespace pap
