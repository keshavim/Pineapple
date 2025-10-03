#include "db_result.h"
#include <sstream>


DBResult::DBResult() = default;

DBResult::DBResult(nanodbc::result &r)
{
    const short cols = r.columns();
    while (r.next())
    {
        std::vector<std::string> row;
        for (short i = 0; i < cols; ++i)
        {
            if (r.is_null(i))
            {
                row.push_back("NULL");
            }
            else
            {
                row.push_back(r.get<std::string>(i));
            }
        }
        data_.push_back(std::move(row));
    }

    for (short i = 0; i < cols; ++i)
    {
        columnNames_.push_back(r.column_name(i));
    }
}

std::optional<std::string> DBResult::get(size_t row, size_t col) const
{
    if (row >= data_.size() || col >= data_[row].size())
        return std::nullopt;
    return data_[row][col];
}

size_t DBResult::rowCount() const
{
    return data_.size();
}
size_t DBResult::colCount() const
{
    return columnNames_.size();
}

std::string DBResult::toString() const
{
    std::ostringstream oss;
    // Header
    for (const auto &name : columnNames_)
    {
        oss << name << "\t";
    }
    oss << "\n";

    // Rows
    for (const auto &row : data_)
    {
        for (const auto &val : row)
        {
            oss << val << "\t";
        }
        oss << "\n";
    }
    return oss.str();
}
