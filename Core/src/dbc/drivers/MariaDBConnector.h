#ifndef MARIADATABASE_H
#define MARIADATABASE_H

#include "../DBConnector.h"
#include <conncpp.hpp>
#include <memory>
#include <mutex>

namespace pap
{

class MariaDatabase : public DBConnector
{
public:
    MariaDatabase() = default;
    ~MariaDatabase() override = default;

    Result<void> connect(const std::string &uri,
                         const std::string &user,
                         const std::string &password,
                         const std::string &database) override;

    bool isConnected() const override;

    Result<DBResult> executeQuery(const std::string &query) override;

private:
    std::unique_ptr<sql::Connection> m_Connection;
    mutable std::mutex m_ConnMutex;
};

} // namespace pap

#endif // MARIADATABASE_H
