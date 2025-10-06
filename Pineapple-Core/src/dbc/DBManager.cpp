#include "pinepch.h"

#include "DBManager.h"
#include "drivers/MariaDBConnector.h"


namespace pap {

// only if your database interface currently throws

Result<void> DBManager::connect(
    DBDriver driver,
    const std::string& uri,
    const std::string& user,
    const std::string& password,
    const std::string& database)
{
    switch (driver) {
        case DBDriver::MariaDB:
            m_Database = std::make_unique<MariaDatabase>();
            break;

        // case DBDriver::MySQL:
        //     m_Database = std::make_unique<MySQLDatabase>();
        //     break;

        default:
            return std::unexpected("[DBManager] Unsupported driver");
    }

    // Assuming m_Database->connect returns bool (true = success, false = fail)
    if (!m_Database->connect(uri, user, password, database)) {
        return std::unexpected("[DBManager] Failed to connect to database");
    }

    return {}; // success (void expected)
}


bool DBManager::isConnected() const {
    return m_Database && m_Database->isConnected();
}

Result<DBResult> DBManager::executeQuery(const std::string& query) {
    assert(m_Database && "[DBManager] No database driver initialized");
    return m_Database->executeQuery(query);
}

} // namespace pap
