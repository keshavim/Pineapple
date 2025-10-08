#pragma once
#include <string>
#include <vector>
#include <expected>
#include <memory>
#include <mutex>
#include "core/core.h"

namespace pap
{

    // ───────────── Schema Types ─────────────

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

    struct DBResult;

    // ───────────── Interface ─────────────

    class DBConnector
    {
    public:
        virtual ~DBConnector() = default;

        // Connection Management
        virtual Result<void> connect(const std::string &uri,
                                     const std::string &user,
                                     const std::string &password) = 0;

        virtual void disconnect() = 0;
        virtual bool isConnected() const = 0;


        // Query Execution
        virtual Result<DBResult> executeQuery(const std::string &query) = 0;
        virtual Result<void> dryRun(const std::string &query) { return {}; }

        // Transactions
        virtual Result<void> beginTransaction() = 0;
        virtual Result<void> commitTransaction() = 0;
        virtual Result<void> rollbackTransaction() = 0;

        // Metadata / Connection Info
        virtual Result<std::string> getServerVersion() const = 0;
    };

    // Factory helper
    std::unique_ptr<DBConnector> createMariaDatabase();
}
