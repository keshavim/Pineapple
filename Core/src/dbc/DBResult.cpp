#include "conncpp/ResultSet.hpp"
#include "conncpp/ResultSetMetaData.hpp"
#include "pinepch.h"
#include "DBResult.h"
#include <cassert>
#include <stdexcept>
#include <sstream>

namespace pap
{
    DBResult::DBResult(sql::ResultSet* rs)
    {
        assert(rs != nullptr && "ResultSet cannot be null");
        populateFromResultSet(rs);
    }

    Result<std::string> DBResult::getColumnName(size_t index) const
    {
        if (index >= m_ColumnNames.size())
            return std::unexpected("Column index out of range");
        return m_ColumnNames[index];
    }

    Result<std::string> DBResult::getValue(size_t row, size_t col) const
    {
        if (row >= m_Data.size())
            return std::unexpected("Row index out of range");
        if (col >= m_ColumnNames.size())
            return std::unexpected("Column index out of range");

        return m_Data[row][col];
    }

    Result<std::string> DBResult::getValue(size_t row, const std::string& colName) const
    {
        auto it = std::find(m_ColumnNames.begin(), m_ColumnNames.end(), colName);
        if (it == m_ColumnNames.end())
            return std::unexpected("Column name not found: " + colName);

        size_t colIndex = static_cast<size_t>(std::distance(m_ColumnNames.begin(), it));
        return getValue(row, colIndex);
    }

    Result<std::vector<std::string>> DBResult::getRow(size_t row) const
    {
        if (row >= m_Data.size())
            return std::unexpected("Row index out of range");
        return m_Data[row];
    }

    Result<std::string> DBResult::getColumnType(size_t col) const
    {
        if (col >= m_ColumnTypes.size())
            return std::unexpected("Column index out of range");
        return m_ColumnTypes[col];
    }

    Result<std::string> DBResult::getTableName(size_t col) const
    {
        if (col >= m_TableNames.size())
            return std::unexpected("Column index out of range");
        return m_TableNames[col];
    }

    void DBResult::populateFromResultSet(sql::ResultSet* rs)
    {
        auto meta = rs->getMetaData();
        const int columnCount = meta->getColumnCount();

        m_ColumnNames.reserve(columnCount);
        m_ColumnTypes.reserve(columnCount);
        m_TableNames.reserve(columnCount);

        for (int i = 1; i <= columnCount; ++i)
        {
            m_ColumnNames.push_back(meta->getColumnLabel(i).c_str());
            m_ColumnTypes.push_back(meta->getColumnTypeName(i).c_str());
            m_TableNames.push_back(meta->getTableName(i).c_str());
        }

        while (rs->next())
        {
            std::vector<std::string> row;
            row.reserve(columnCount);

            for (int i = 1; i <= columnCount; ++i)
            {
                row.push_back(rs->getString(i).c_str());
            }

            m_Data.push_back(std::move(row));
        }
    }

    std::string DBResult::toString() const
    {
        std::ostringstream oss;

        // Header
        for (const auto& col : m_ColumnNames)
            oss << col << "\t";
        oss << "\n";

        // Rows
        for (const auto& row : m_Data)
        {
            for (const auto& cell : row)
                oss << cell << "\t";
            oss << "\n";
        }

        return oss.str();
    }

    std::ostream& operator<<(std::ostream& os, const DBResult& res)
    {
        return os << res.toString();
    }
} // namespace pap
