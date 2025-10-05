


// db_manager.h
#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include "db_result.h"
#include <mariadbc/conncpp.hpp>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>

namespace pap
{
class DBManager
{
public:
    DBManager() = default;
    ~DBManager() = default;

    bool connect(const std::string &uri,
                 const std::string &user,
                 const std::string &password,
                 const std::string &database);
    bool isConnected() const;

    DBResult executeQuery(const std::string &query);

private:
    std::unique_ptr<sql::Connection> connection;
    mutable std::mutex connMutex; // For thread safety
};
} // namespace pap
#endif // DB_MANAGER_H
