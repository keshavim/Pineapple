#include "DBManager.h"
#include "drivers/MariaDBConnector.h"
#include <stdexcept>

namespace pap {

bool DBManager::connect(DBDriver driver,
                        const std::string& uri,
                        const std::string& user,
                        const std::string& password,
                        const std::string& database) {
    switch (driver) {
        case DBDriver::MariaDB:
            m_Database = std::make_unique<MariaDatabase>();
            break;
        // case DBDriver::MySQL:
        //     m_Database = std::make_unique<MySQLDatabase>();
        //     break;
        default:
            throw std::invalid_argument("[DBManager] Unsupported driver");
    }

    return m_Database->connect(uri, user, password, database);
}

bool DBManager::isConnected() const {
    return m_Database && m_Database->isConnected();
}

DBResult DBManager::executeQuery(const std::string& query) {
    if (!m_Database) {
        throw std::runtime_error("[DBManager] No database driver initialized");
    }
    return m_Database->executeQuery(query);
}

} // namespace pap
