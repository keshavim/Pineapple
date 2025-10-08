#pragma once

#include <string>
#include <vector>
#include <expected>
#include <ostream>
#include <cstddef>
#include <core/core.h>


namespace sql {
    class ResultSet;
}

namespace pap
{

    struct DBResult
    {
    public:
        DBResult() = default;
        explicit DBResult(sql::ResultSet* rs);

        // Row / column info
        size_t getRowCount() const noexcept { return m_Data.size(); }
        size_t getColumnCount() const noexcept { return m_ColumnNames.size(); }

        const std::vector<std::string>& getColumnNames() const noexcept { return m_ColumnNames; }

        // Data access with error handling via Result
        Result<std::string> getColumnName(size_t index) const;
        Result<std::string> getValue(size_t row, size_t col) const;
        Result<std::string> getValue(size_t row, const std::string& colName) const;
        Result<std::vector<std::string>> getRow(size_t row) const;
        Result<std::string> getColumnType(size_t col) const;
        Result<std::string> getTableName(size_t col) const;

        // Utility
        std::string toString() const;

        friend std::ostream& operator<<(std::ostream& os, const DBResult& res);

    private:
        std::vector<std::string> m_ColumnTypes;
        std::vector<std::string> m_TableNames;
        std::vector<std::string> m_ColumnNames;
        std::vector<std::vector<std::string>> m_Data;

        void populateFromResultSet(sql::ResultSet* rs);
    };
} // namespace pap

// C++20/23 std::formatter specialization
template <>
struct std::formatter<pap::DBResult> : std::formatter<std::string>
{
    auto format(const pap::DBResult& res, auto& ctx)
    {
        return std::formatter<std::string>::format(res.toString(), ctx);
    }
};
