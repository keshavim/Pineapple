#include "QueryData.h"
#include "conncpp/ResultSet.hpp"
#include "conncpp/ResultSetMetaData.hpp"
#include <algorithm>
#include <cassert>
#include <sstream>

namespace pap
{
namespace db
{


QueryData::QueryData(sql::ResultSet *rs) : m_Columns(buildColumns(rs)), m_Data(buildData(rs))
{
    assert(rs && "ResultSet cannot be null");
}

std::vector<ResultColumnInfo> QueryData::buildColumns(sql::ResultSet *rs)
{
    auto meta = rs->getMetaData();
    const int columnCount = meta->getColumnCount();

    std::vector<ResultColumnInfo> cols;
    cols.reserve(columnCount);

    for (int i = 1; i <= columnCount; ++i)
    {
        cols.push_back(ResultColumnInfo{meta->getColumnLabel(i).c_str(),
                                        meta->getColumnTypeName(i).c_str(),
                                        meta->getTableName(i).c_str()});
    }
    return cols;
}

std::vector<std::vector<std::string>> QueryData::buildData(sql::ResultSet *rs)
{
    auto meta = rs->getMetaData();
    const int columnCount = meta->getColumnCount();

    std::vector<std::vector<std::string>> rows;

    while (rs->next())
    {
        std::vector<std::string> row;
        row.reserve(columnCount);

        for (int i = 1; i <= columnCount; ++i)
            row.push_back(rs->getString(i).c_str());

        rows.push_back(std::move(row));
    }
    return rows;
}

Result<std::string> QueryData::getColumnName(size_t index) const
{
    if (index >= m_Columns.size())
        return std::unexpected(Error{ErrorCode::ColumnIndexOutOfRange});
    return m_Columns[index].name;
}

Result<std::string> QueryData::getValue(size_t row, size_t col) const
{
    if (row >= m_Data.size())
        return std::unexpected(Error{ErrorCode::RowIndexOutOfRange});
    if (col >= m_Columns.size())
        return std::unexpected(Error{ErrorCode::ColumnIndexOutOfRange});
    return m_Data[row][col];
}

Result<std::string> QueryData::getValue(size_t row, const std::string &colName) const
{
    auto it =
        std::find_if(m_Columns.begin(), m_Columns.end(), [&](const ResultColumnInfo &c) { return c.name == colName; });
    if (it == m_Columns.end())
        return std::unexpected(Error{ErrorCode::ColumnNameNotFound});

    size_t colIndex = static_cast<size_t>(std::distance(m_Columns.begin(), it));
    return getValue(row, colIndex);
}

Result<std::vector<std::string>> QueryData::getRow(size_t row) const
{
    if (row >= m_Data.size())
        return std::unexpected(Error{ErrorCode::RowIndexOutOfRange});
    return m_Data[row];
}

Result<std::string> QueryData::getColumnType(size_t col) const
{
    if (col >= m_Columns.size())
        return std::unexpected(Error{ErrorCode::ColumnIndexOutOfRange});
    return m_Columns[col].type;
}

Result<std::string> QueryData::getTableName(size_t col) const
{
    if (col >= m_Columns.size())
        return std::unexpected(Error{ErrorCode::ColumnIndexOutOfRange});
    return m_Columns[col].table;
}

std::string QueryData::toString() const
{
    std::ostringstream oss;

    for (const auto &col : m_Columns)
        oss << col.name << "\t";
    oss << "\n";

    for (const auto &row : m_Data)
    {
        for (const auto &cell : row)
            oss << cell << "\t";
        oss << "\n";
    }
    return oss.str();
}

std::ostream &operator<<(std::ostream &os, const QueryData &res)
{
    return os << res.toString();
}
} // namespace db
} // namespace pap
