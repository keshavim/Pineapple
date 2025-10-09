#pragma once
#include <string>
#include <vector>

namespace pap
{
namespace db
{


struct ColumnInfo
{
    std::string name;
    std::string type;
    bool isNullable;
    bool isPrimaryKey;
};

struct TableInfo
{
    std::string name;
    std::vector<ColumnInfo> columns;
};

struct SchemaInfo
{
    std::string name;
    std::vector<TableInfo> tables;
};
} // namespace db
} // namespace pap
