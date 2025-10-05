// DBResult.cpp
#include "pinepch.h"
#include "db_result.h"


void DBResult::populateFromResultSet(sql::ResultSet* rs) {
    if (!rs) {
        throw std::invalid_argument("ResultSet is null");
    }

    sql::ResultSetMetaData* meta = rs->getMetaData();
    size_t colCount = meta->getColumnCount();
    std::cout << "metadata" << std::endl;
    // Populate column names, types, table names
    m_ColumnNames.reserve(colCount);
    m_ColumnTypes.reserve(colCount);
    m_TableNames.reserve(colCount);
    for (size_t i = 1; i <= colCount; ++i) { // 1-based index
        m_ColumnNames.push_back(meta->getColumnLabel(i).c_str());
        m_ColumnTypes.push_back(meta->getColumnTypeName(i).c_str());
        m_TableNames.push_back(meta->getTableName(i).c_str());
    }

    std::cout << "populate" << std::endl;

    // Populate data
    while (rs->next()) {
        std::vector<std::string> row;
        row.reserve(colCount);
        for (size_t i = 1; i <= colCount; ++i) {
            sql::SQLString val = rs->getString(i);
            row.push_back(val.c_str());
        }
        m_Data.push_back(row);
    }
    std::cerr << "complete" << std::endl;

}

DBResult::DBResult(sql::ResultSet* rs) {
    populateFromResultSet(rs);
}

size_t DBResult::getRowCount() const {
    return m_Data.size();
}

size_t DBResult::getColumnCount() const {
    return m_ColumnNames.size();
}

std::string DBResult::getColumnName(size_t index) const {
    if (index >= m_ColumnNames.size()) {
        throw std::out_of_range("Column index out of range");
    }
    return m_ColumnNames[index];
}

std::vector<std::string> DBResult::getColumnNames() const {
    return m_ColumnNames;
}

std::string DBResult::getValue(size_t row, size_t col) const {
    if (row >= m_Data.size() || col >= m_ColumnNames.size()) {
        throw std::out_of_range("Row or column index out of range");
    }
    return m_Data[row][col];
}

std::string DBResult::getValue(size_t row, const std::string& colName) const {
    auto it = std::find(m_ColumnNames.begin(), m_ColumnNames.end(), colName);
    if (it == m_ColumnNames.end()) {
        throw std::invalid_argument("Column name not found");
    }
    size_t col = std::distance(m_ColumnNames.begin(), it);
    return getValue(row, col);
}

std::vector<std::string> DBResult::getRow(size_t row) const {
    if (row >= m_Data.size()) {
        throw std::out_of_range("Row index out of range");
    }
    return m_Data[row];
}

std::string DBResult::getColumnType(size_t col) const {
    if (col >= m_ColumnTypes.size()) {
        throw std::out_of_range("Column index out of range");
    }
    return m_ColumnTypes[col];
}

std::string DBResult::getTableName(size_t col) const {
    if (col >= m_TableNames.size()) {
        throw std::out_of_range("Column index out of range");
    }
    return m_TableNames[col];
}

std::string DBResult::toString() const {
    std::stringstream ss;

    // Determine column widths
    std::vector<size_t> colWidths(m_ColumnNames.size(), 0);

    // Check header widths
    for (size_t i = 0; i < m_ColumnNames.size(); ++i) {
        colWidths[i] = m_ColumnNames[i].size();
    }

    // Check each row for max width per column
    for (const auto& row : m_Data) {
        for (size_t i = 0; i < row.size(); ++i) {
            colWidths[i] = std::max(colWidths[i], row[i].size());
        }
    }

    // Print column names with formatting
    for (size_t i = 0; i < m_ColumnNames.size(); ++i) {
        ss << std::format("{:<{}}  ", m_ColumnNames[i], colWidths[i]);
    }
    ss << "\n";

    // Print separator
    for (size_t i = 0; i < colWidths.size(); ++i) {
        ss << std::format("{:-<{}}  ", "", colWidths[i]);
    }
    ss << "\n";

    // Print rows
    for (const auto& row : m_Data) {
        for (size_t i = 0; i < row.size(); ++i) {
            ss << std::format("{:<{}}  ", row[i], colWidths[i]);
        }
        ss << "\n";
    }

    return ss.str();
}

// operator<< just calls toString()
std::ostream& operator<<(std::ostream& os, const DBResult& res) {
    os << res.toString();
    return os;
}
