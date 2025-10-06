#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <memory>
#include <string>
#include "DBResult.h"
#include "DBConnector.h"

namespace pap {

enum class DBDriver {
    MariaDB,
    // MySQL,
    // SQLite,
    // PostgreSQL
};

class DBManager {
public:
    DBManager() = default;
    ~DBManager() = default;

    bool connect(DBDriver driver,
                 const std::string& uri,
                 const std::string& user,
                 const std::string& password,
                 const std::string& database);

    bool isConnected() const;

    DBResult executeQuery(const std::string& query);

private:
    std::unique_ptr<DBConnector> m_Database;
};

} // namespace pap

#endif // DBMANAGER_H
