#include "pinepch.h"

#include "DBManager.h"
#include "drivers/MariaDBConnector.h"


namespace pap {

// only if your database interface currently throws

// Define the static member
std::unique_ptr<DBConnector> DBManager::s_Database = nullptr;

Result<void> DBManager::connect(
    DBDriver driver,
    const std::string& uri,
    const std::string& user,
    const std::string& password,
    const std::string& database)
{
    switch (driver) {
        case DBDriver::MariaDB:
            s_Database = std::make_unique<MariaDatabase>();
            break;

        // case DBDriver::MySQL:
        //     s_Database = std::make_unique<MySQLDatabase>();
        //     break;

        default:
            return std::unexpected("[DBManager] Unsupported driver");
    }

    if (!s_Database->connect(uri, user, password, database)) {
        return std::unexpected("[DBManager] Failed to connect to database");
    }

    return {};
}

bool DBManager::isConnected() {
    return s_Database && s_Database->isConnected();
}

Result<DBResult> DBManager::executeQuery(const std::string& query) {
    assert(s_Database && "[DBManager] No database driver initialized");
    return s_Database->executeQuery(query);
}

} // namespace pap
