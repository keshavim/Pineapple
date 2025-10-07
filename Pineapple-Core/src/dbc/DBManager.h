#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "DBConnector.h"
#include "DBResult.h"
#include <expected>
#include <memory>
#include <string>


namespace pap
{


enum class DBDriver
{
    MariaDB,
    // MySQL,
    // SQLite,
    // PostgreSQL
};

class DBManager
{
public:
    DBManager() = delete;
    ~DBManager() = delete;
    DBManager(const DBManager &) = delete;
    DBManager &operator=(const DBManager &) = delete;

    static Result<void> connect(DBDriver driver,
                                const std::string &uri,
                                const std::string &user,
                                const std::string &password,
                                const std::string &database);

    static bool isConnected();

    static Result<DBResult> executeQuery(const std::string &query);

private:
    static std::unique_ptr<DBConnector> s_Database;
};

} // namespace pap

#endif // DBMANAGER_H
