// DBResult.h
#ifndef DBRESULT_H
#define DBRESULT_H
#include <core/core.h>
#include <mariadbc/conncpp.hpp>

namespace pap{
class DBResult
{
public:
    // Constructor from ResultSet
    DBResult(sql::ResultSet *rs);

    // Immutable getters
    size_t getRowCount() const;
    size_t getColumnCount() const;
    Result<std::string> getColumnName(size_t index) const;

    const std::vector<std::string> &getColumnNames() const;

    Result<std::string> getValue(size_t row, size_t col) const;

    Result<std::string> getValue(size_t row, const std::string &colName) const;

    Result<std::vector<std::string>> getRow(size_t row) const;

    Result<std::string> getColumnType(size_t col) const;

    Result<std::string> getTableName(size_t col) const;


    // toString
    std::string toString() const;

    // Operator overload for printing
    friend std::ostream &operator<<(std::ostream &os, const DBResult &res);

private:
    std::vector<std::string> m_ColumnTypes;
    std::vector<std::string> m_TableNames;
    std::vector<std::string> m_ColumnNames;
    std::vector<std::vector<std::string>> m_Data;

    // Helper to populate from ResultSet
    void populateFromResultSet(sql::ResultSet *rs);
};
}
// C++20/23 std::formatter specialization
template <>
struct std::formatter<pap::DBResult> : std::formatter<std::string>
{
    // parse is inherited from std::formatter<std::string>

    auto format(const pap::DBResult &res, auto &ctx)
    {
        // Use DBResult::toString()
        return std::formatter<std::string>::format(res.toString(), ctx);
    }
};
#endif // DBRESULT_H
