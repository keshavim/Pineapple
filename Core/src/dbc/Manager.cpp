#include "Manager.h"
#include "QueryData.h"
#include "drivers/MariaDB.h"

namespace pap
{
namespace db
{

    
Result<void> Manager::connect(const ConnectInfo &info)
{
    std::shared_ptr<Connector> conn;

    switch (info.driver)
    {
    case Driver::Maria:
        conn = std::make_shared<MariaDatabase>();
        break;
    default:
        return std::unexpected(Error{ErrorCode::UnsupportedDriver});
    }

    auto res = conn->connect(info);
    if (!res)
        return std::unexpected(res.error());

    m_CurrentConnection = conn;

    auto it = std::find(m_Connections.begin(), m_Connections.end(), info);
    if (it == m_Connections.end())
    {
        m_Connections.push_back(info);
    }

    return {};
}

void Manager::disconnect()
{
    if (m_CurrentConnection)
    {
        m_CurrentConnection->disconnect();
        m_CurrentConnection.reset();
        m_CurrentSchema.reset();
    }
}

bool Manager::isConnected() const
{
    return m_CurrentConnection && m_CurrentConnection->isConnected();
}

Result<QueryData> Manager::executeQuery(const std::string &query)
{
    if (!m_CurrentConnection)
        return std::unexpected(Error{ErrorCode::NoConnection});

    return m_CurrentConnection->executeQuery(query);
}

Result<void> Manager::dryRun(const std::string &query)
{
    if (!m_CurrentConnection)
        return std::unexpected(Error{ErrorCode::NoConnection});

    return m_CurrentConnection->dryRun(query);
}

Result<void> Manager::beginTransaction()
{
    if (!m_CurrentConnection)
        return std::unexpected(Error{ErrorCode::NoConnection});

    return m_CurrentConnection->beginTransaction();
}

Result<void> Manager::commitTransaction()
{
    if (!m_CurrentConnection)
        return std::unexpected(Error{ErrorCode::NoConnection});

    return m_CurrentConnection->commitTransaction();
}

Result<void> Manager::rollbackTransaction()
{
    if (!m_CurrentConnection)
        return std::unexpected(Error{ErrorCode::NoConnection});

    return m_CurrentConnection->rollbackTransaction();
}

Result<std::vector<std::string>> Manager::listSchemas()
{
    if (!m_CurrentConnection)
        return std::unexpected(Error{ErrorCode::NoConnection});

    auto res = m_CurrentConnection->executeQuery("SHOW DATABASES;");
    if (!res)
        return std::unexpected(res.error());

    std::vector<std::string> schemas;
    for (size_t i = 0; i < res->getRowCount(); ++i)
    {
        auto row = res->getRow(i);
        if (!row)
            return std::unexpected(row.error());
        schemas.push_back((*row)[0]);
    }

    return schemas;
}

Result<void> Manager::switchSchema(const std::string &schema)
{
    if (!m_CurrentConnection)
        return std::unexpected(Error{ErrorCode::NoConnection});

    auto res = m_CurrentConnection->executeQuery("USE " + schema + ";");
    if (!res)
        return std::unexpected(res.error());

    m_CurrentSchema = schema;
    return {};
}

Result<std::vector<TableInfo>> Manager::listTables(const std::string &schema)
{
    if (!m_CurrentConnection)
        return std::unexpected(Error{ErrorCode::NoConnection});

    auto res = m_CurrentConnection->executeQuery("SHOW TABLES FROM " + schema + ";");
    if (!res)
        return std::unexpected(res.error());

    std::vector<TableInfo> tables;
    for (size_t i = 0; i < res->getRowCount(); ++i)
    {
        auto row = res->getRow(i);
        if (!row)
            return std::unexpected(row.error());

        tables.push_back({(*row)[0], {}});
    }

    return tables;
}

Result<TableInfo> Manager::getTableInfo(const std::string &schema, const std::string &table)
{
    if (!m_CurrentConnection)
        return std::unexpected(Error{ErrorCode::NoConnection});

    auto res = m_CurrentConnection->executeQuery("SHOW COLUMNS FROM " + schema + "." + table + ";");
    if (!res)
        return std::unexpected(res.error());

    TableInfo tinfo;
    tinfo.name = table;

    for (size_t i = 0; i < res->getRowCount(); ++i)
    {
        auto row = res->getRow(i);
        if (!row)
            return std::unexpected(row.error());

        ColumnInfo col;
        col.name = (*row)[0];
        col.type = (*row)[1];
        col.isNullable = ((*row)[2] == "YES");
        col.isPrimaryKey = ((*row)[3] == "PRI");
        tinfo.columns.push_back(col);
    }

    return tinfo;
}
} // namespace db
} // namespace pap
