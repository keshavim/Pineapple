#include "MariaDBConnector.h"
#include <cstdio>
#include <stdexcept>

namespace pap {

bool MariaDatabase::connect(const std::string& uri,
                            const std::string& user,
                            const std::string& password,
                            const std::string& database) {
    try {
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        sql::Properties props({{"user", user}, {"password", password}});
        m_Connection.reset(driver->connect(uri, props));
        m_Connection->setSchema(database);
        m_Connection->setAutoCommit(true);
        return m_Connection != nullptr;
    } catch (const sql::SQLException& e) {
        std::fprintf(stderr, "[MariaDatabase] Connection failed: %s\n", e.what());
        return false;
    }
}

bool MariaDatabase::isConnected() const {
    //std::scoped_lock lock(m_ConnMutex);
    return m_Connection != nullptr && m_Connection->isValid();
}

DBResult MariaDatabase::executeQuery(const std::string& query) {
    //std::scoped_lock lock(m_ConnMutex);

    if (!isConnected()) {
        throw std::runtime_error("[MariaDatabase] No active database connection");
    }

    try {
        std::unique_ptr<sql::Statement> stmt(m_Connection->createStatement());
        std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery(query));
        return DBResult(rs.release()); // DBResult takes ownership of pointer
    } catch (const sql::SQLException& e) {
        std::fprintf(stderr, "[MariaDatabase] Query failed: %s\n", e.what());
        throw;
    }
}

} // namespace pap
