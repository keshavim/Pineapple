#pragma once
#include "DBConnector.h"
#include "drivers/MariaDB.h"
#include "dbc/DBResult.h"

namespace pap
{
    enum class DBDriver
    {
        MariaDB,
        // MySQL, PostgreSQL, SQLite etc. can be added later
    };

    struct ConnectInfo
    {
        DBDriver driver;
        std::string uri;
        std::string user;
        std::string password;

        bool operator==(const ConnectInfo& other) const
        {
            return driver == other.driver &&
                   uri == other.uri &&
                   user == other.user &&
                   password == other.password;
        }
    };

    class DBManager
    {
    public:
        DBManager() = default;

        // Connection management
        Result<void> connect(const ConnectInfo& info);
        void disconnect();
        bool isConnected() const;

        // Query execution
        Result<DBResult> executeQuery(const std::string& query);
        Result<void> dryRun(const std::string& query);

        // Transactions
        Result<void> beginTransaction();
        Result<void> commitTransaction();
        Result<void> rollbackTransaction();

        // Schema management
        Result<std::vector<std::string>> listSchemas();
        Result<void> switchSchema(const std::string& schema);
        Result<std::vector<TableInfo>> listTables(const std::string& schema);
        Result<TableInfo> getTableInfo(const std::string& schema, const std::string& table);
        std::optional<std::string> currentSchema() const { return m_CurrentSchema; }

        // Connection history
        const std::vector<ConnectInfo>& getConnections() const { return m_Connections; }
        std::shared_ptr<DBConnector> currentConnection() const { return m_CurrentConnection; }

    private:
        std::vector<ConnectInfo> m_Connections;
        std::shared_ptr<DBConnector> m_CurrentConnection;
        std::optional<std::string> m_CurrentSchema;
    };
}
