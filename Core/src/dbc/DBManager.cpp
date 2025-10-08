#include "DBManager.h"

namespace pap
{
    Result<void> DBManager::connect(const ConnectInfo& info)
    {


        // Create new connector instance
        std::shared_ptr<DBConnector> conn;
        switch (info.driver)
        {
        case DBDriver::MariaDB:
            conn = createMariaDatabase();
            break;
        default:
            return std::unexpected("Unsupported driver");
        }

        // Connect
        auto res = conn->connect(info.uri, info.user, info.password);
        if (!res) return std::unexpected(res.error());

        m_CurrentConnection = conn;
        // Check for duplicate connection
        auto it = std::find(m_Connections.begin(), m_Connections.end(), info);
        if (it == m_Connections.end())
        {
            m_Connections.push_back(info);
        }

        return {};
    }

    void DBManager::disconnect()
    {
        if (m_CurrentConnection)
        {
            m_CurrentConnection->disconnect();
            m_CurrentConnection.reset();
            m_CurrentSchema.reset();
        }
    }

    bool DBManager::isConnected() const
    {
        return m_CurrentConnection && m_CurrentConnection->isConnected();
    }

    Result<DBResult> DBManager::executeQuery(const std::string& query)
    {
        assert(m_CurrentConnection && "No current connection");
        return m_CurrentConnection->executeQuery(query);
    }

    Result<void> DBManager::dryRun(const std::string& query)
    {
        assert(m_CurrentConnection && "No current connection");
        return m_CurrentConnection->dryRun(query);
    }

    Result<void> DBManager::beginTransaction()
    {
        assert(m_CurrentConnection && "No current connection");
        return m_CurrentConnection->beginTransaction();
    }

    Result<void> DBManager::commitTransaction()
    {
        assert(m_CurrentConnection && "No current connection");
        return m_CurrentConnection->commitTransaction();
    }

    Result<void> DBManager::rollbackTransaction()
    {
        assert(m_CurrentConnection && "No current connection");
        return m_CurrentConnection->rollbackTransaction();
    }

    Result<std::vector<std::string>> DBManager::listSchemas()
    {
        assert(m_CurrentConnection && "No current connection");

        auto res = m_CurrentConnection->executeQuery("SHOW DATABASES;");
        if (!res) return std::unexpected(res.error());

        std::vector<std::string> schemas;
        for (size_t i = 0; i < res->getRowCount(); ++i)
        {
            auto row = res->getRow(i);
            if (!row) return std::unexpected(row.error());
            schemas.push_back((*row)[0]);
        }
        return schemas;
    }

    Result<void> DBManager::switchSchema(const std::string& schema)
    {
        assert(m_CurrentConnection && "No current connection");

        auto res = m_CurrentConnection->executeQuery("USE " + schema + ";");
        if (!res) return std::unexpected(res.error());

        m_CurrentSchema = schema;
        return {};
    }

    Result<std::vector<TableInfo>> DBManager::listTables(const std::string& schema)
    {
        assert(m_CurrentConnection && "No current connection");

        auto res = m_CurrentConnection->executeQuery("SHOW TABLES FROM " + schema + ";");
        if (!res) return std::unexpected(res.error());

        std::vector<TableInfo> tables;
        for (size_t i = 0; i < res->getRowCount(); ++i)
        {
            auto row = res->getRow(i);
            if (!row) return std::unexpected(row.error());
            tables.push_back({ (*row)[0], {} });
        }
        return tables;
    }

    Result<TableInfo> DBManager::getTableInfo(const std::string& schema, const std::string& table)
    {
        assert(m_CurrentConnection && "No current connection");

        auto res = m_CurrentConnection->executeQuery("SHOW COLUMNS FROM " + schema + "." + table + ";");
        if (!res) return std::unexpected(res.error());

        TableInfo tinfo;
        tinfo.name = table;
        for (size_t i = 0; i < res->getRowCount(); ++i)
        {
            auto row = res->getRow(i);
            if (!row) return std::unexpected(row.error());

            ColumnInfo col;
            col.name = (*row)[0];
            col.type = (*row)[1];
            col.isNullable = ((*row)[2] == "YES");
            col.isPrimaryKey = ((*row)[3] == "PRI");
            tinfo.columns.push_back(col);
        }
        return tinfo;
    }
}
