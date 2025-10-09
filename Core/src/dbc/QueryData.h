#pragma once

#include <cstddef>
#include <expected>
#include <format>
#include <ostream>
#include <string>
#include <vector>

#include "Error.h"
#include "Schema.h"
#include <core/core.h>

namespace sql
{
class ResultSet;
}

namespace pap
{
namespace db
{
// Immutable column info for query results
struct ResultColumnInfo
{
    const std::string name;
    const std::string type;
    const std::string table;
};

class QueryData
{
public:
    explicit QueryData(sql::ResultSet *rs);

    size_t getRowCount() const noexcept
    {
        return m_Data.size();
    }
    size_t getColumnCount() const noexcept
    {
        return m_Columns.size();
    }

    const std::vector<ResultColumnInfo> &getColumns() const noexcept
    {
        return m_Columns;
    }

    Result<std::string> getColumnName(size_t index) const;
    Result<std::string> getValue(size_t row, size_t col) const;
    Result<std::string> getValue(size_t row, const std::string &colName) const;
    Result<std::vector<std::string>> getRow(size_t row) const;
    Result<std::string> getColumnType(size_t col) const;
    Result<std::string> getTableName(size_t col) const;

    std::string toString() const;
    friend std::ostream &operator<<(std::ostream &os, const QueryData &res);

private:
    const std::vector<ResultColumnInfo> m_Columns;
    const std::vector<std::vector<std::string>> m_Data;

    static std::vector<ResultColumnInfo> buildColumns(sql::ResultSet *rs);
    static std::vector<std::vector<std::string>> buildData(sql::ResultSet *rs);
};
} // namespace db
} // namespace pap

// Formatter
template <>
struct std::formatter<pap::db::QueryData> : std::formatter<std::string>
{
    auto format(const pap::db::QueryData &res, auto &ctx)
    {
        return std::formatter<std::string>::format(res.toString(), ctx);
    }
};
