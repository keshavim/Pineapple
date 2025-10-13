#pragma once
#include "Connector.h"
#include "Schema.h"
#include "dbc/Error.h"
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

namespace pap {
namespace db {

class Connector;
class QueryData;

class Manager
{
public:
    Manager() = default;

    // connect: opens a new connection and stores it in the pool.
    // On success this creates a Connector instance owned by the manager
    // and adds a ConnectInfo copy to the saved connections list.
    Result<void> connect(const ConnectInfo &info);

    // Disconnect the currently-active connection (does not drop it from pool).
    void disconnectCurrent();

    // Close and remove a connection by index (removes both info and connector).
    Result<void> closeConnection(size_t index);

    // Switch which connection is current (by index into pool / saved connections).
    Result<void> setCurrentConnection(size_t index);

    bool isConnected() const;

    // Query execution on current connection
    Result<QueryData> executeQuery(const std::string &query);
    Result<void> dryRun(const std::string &query);

    // Transactions on current connection
    Result<void> beginTransaction();
    Result<void> commitTransaction();
    Result<void> rollbackTransaction();

    // Schema management on current connection
    Result<std::vector<std::string>> listSchemas();
    Result<void> switchSchema(const std::string &schema);
    Result<std::vector<TableInfo>> listTables(const std::string &schema);
    Result<TableInfo> getTableInfo(const std::string &schema, const std::string &table);

    // Connection history / saved infos (owned copy)
    const std::vector<ConnectInfo> &getConnections() const { return m_Connections; }

    // Retrieve current connection shared_ptr (may be nullptr)
    std::shared_ptr<Connector> currentConnection() const { return m_CurrentConnection; }

    // Number of open connections
    size_t connectionCount() const { return m_ConnectionPool.size(); }

private:
    // stored data
    std::vector<ConnectInfo> m_Connections;                 // owned copies of connection info
    std::vector<std::shared_ptr<Connector>> m_ConnectionPool; // owned connectors (parallel to m_Connections)
    std::shared_ptr<Connector> m_CurrentConnection;         // pointer into m_ConnectionPool (or nullptr)
    std::optional<std::string> m_CurrentSchema;
};
} // namespace db
} // namespace pap
