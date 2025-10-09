#pragma once
#include "../Connector.h"
#include <memory>
#include <mutex>
#include <string>

namespace sql
{
class Connection;
class Driver;
class Statement;
class ResultSet;
} // namespace sql

namespace pap
{
namespace db
{
class QueryData;

class MariaDatabase : public Connector
{
public:
    MariaDatabase();
    ~MariaDatabase() override;

    Result<void> connect(const ConnectInfo &info) override;

    void disconnect() override;
    bool isConnected() const override;

    Result<QueryData> executeQuery(const std::string &query) override;
    Result<void> dryRun(const std::string &query) override;

    Result<void> beginTransaction() override;
    Result<void> commitTransaction() override;
    Result<void> rollbackTransaction() override;

private:
    mutable std::mutex m_ConnMutex;
    std::unique_ptr<sql::Connection> m_Connection;
};
} // namespace db
} // namespace pap
