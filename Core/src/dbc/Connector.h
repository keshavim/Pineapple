#pragma once

#include "Error.h"
#include <string>

namespace pap
{
namespace db
{
class QueryData;

// ───────────── Driver Types ─────────────
enum class Driver
{
    Maria,
    // MySQL, PostgreSQL, SQLite etc. can be added later
};

struct ConnectInfo {
    pap::db::Driver driver;
    std::string uri;
    std::string user;
    std::string password;
    bool operator==(ConnectInfo const& o) const = default;
};

// ───────────── Interface ─────────────
class Connector
{
public:
    virtual ~Connector() = default;

    // Connection Management
    virtual Result<void> connect(const ConnectInfo &info) = 0;

    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;

    // Query Execution
    virtual Result<QueryData> executeQuery(const std::string &query) = 0;
    virtual Result<void> dryRun(const std::string &query)
    {
        return {};
    }

    // Transactions
    virtual Result<void> beginTransaction() = 0;
    virtual Result<void> commitTransaction() = 0;
    virtual Result<void> rollbackTransaction() = 0;
};
} // namespace db
} // namespace pap
