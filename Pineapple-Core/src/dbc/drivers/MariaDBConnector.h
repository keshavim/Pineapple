#ifndef MARIADATABASE_H
#define MARIADATABASE_H

#include "../DBConnector.h"
#include <mariadbc/conncpp.hpp>
#include <memory>
#include <mutex>

namespace pap {

class MariaDatabase : public DBConnector {
public:
    MariaDatabase() = default;
    ~MariaDatabase() override = default;

    bool connect(const std::string& uri,
                 const std::string& user,
                 const std::string& password,
                 const std::string& database) override;

    bool isConnected() const override;

    DBResult executeQuery(const std::string& query) override;

private:
    std::unique_ptr<sql::Connection> m_Connection;
    mutable std::mutex m_ConnMutex;
};

} // namespace pap

#endif // MARIADATABASE_H
