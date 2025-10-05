// db_manager.cpp
#include "db_manager.h"

namespace pap {

bool DBManager::connect(const std::string& uri, const std::string& user, const std::string& password, const std::string& database) {
    try {
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        sql::Properties props({{"user", user}, {"password", password}});
        connection.reset(driver->connect(uri, props));

        connection->setSchema(database);

        connection->setAutoCommit(true);
        return connection != nullptr;
    } catch (const sql::SQLException& e) {
        std::fprintf(stderr, "[DBManager] Connection failed: %s\n", e.what());
        return false;
    }
}


bool DBManager::isConnected() const {
    return connection != nullptr && connection->isValid();
}
DBResult DBManager::executeQuery(const std::string& query) {
    if (!isConnected()) {
        throw std::runtime_error("[DBManager] No active database connection");
    }

    try {
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        return DBResult(stmt->executeQuery(query));
    } catch (const sql::SQLException& e) {
        std::fprintf(stderr,
            "[DBManager] Query failed: %s \n",
            e.what());
        throw; // for debugging
    }
}

}
