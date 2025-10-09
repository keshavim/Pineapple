#pragma once
#include "Connector.h"
#include "Schema.h"
#include "dbc/Error.h"
#include <algorithm>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace pap
{

namespace db
{
class Connector;
class QueryData;

class Manager
{
public:
    Manager() = default;

    // Connection management
    Result<void> connect(const ConnectInfo &info);
    void disconnect();
    bool isConnected() const;

    // Query execution
    Result<QueryData> executeQuery(const std::string &query);
    Result<void> dryRun(const std::string &query);

    // Transactions
    Result<void> beginTransaction();
    Result<void> commitTransaction();
    Result<void> rollbackTransaction();

    // Schema management
    Result<std::vector<std::string>> listSchemas();
    Result<void> switchSchema(const std::string &schema);
    Result<std::vector<TableInfo>> listTables(const std::string &schema);
    Result<TableInfo> getTableInfo(const std::string &schema, const std::string &table);
    std::optional<std::string> currentSchema() const
    {
        return m_CurrentSchema;
    }

    // Connection history
    const std::vector<ConnectInfo> &getConnections() const
    {
        return m_Connections;
    }
    std::shared_ptr<Connector> currentConnection() const
    {
        return m_CurrentConnection;
    }

private:
    std::vector<ConnectInfo> m_Connections;
    std::shared_ptr<Connector> m_CurrentConnection;
    std::optional<std::string> m_CurrentSchema;
};
} // namespace db
} // namespace pap
