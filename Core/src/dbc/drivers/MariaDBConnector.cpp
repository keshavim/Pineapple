#include "MariaDBConnector.h"
#include "pinepch.h"
#include <cstdio>
#include <stdexcept>

namespace pap
{

Result<void> MariaDatabase::connect(const std::string &uri,
                                    const std::string &user,
                                    const std::string &password,
                                    const std::string &database)
{
    try
    {
        sql::Driver *driver = sql::mariadb::get_driver_instance();
        sql::Properties props({{"user", user}, {"password", password}});
        m_Connection.reset(driver->connect(uri, props));
        m_Connection->setSchema(database);
        m_Connection->setAutoCommit(true);

        if (!m_Connection)
        {
            return std::unexpected("[MariaDatabase] Connection failed (null)");
        }

        return {}; // success
    }
    catch (const sql::SQLException &e)
    {
        return std::unexpected(std::string("[MariaDatabase] Connection failed: ") + e.what());
    }
}

bool MariaDatabase::isConnected() const
{
    return m_Connection != nullptr && m_Connection->isValid();
}

Result<DBResult> MariaDatabase::executeQuery(const std::string &query)
{
    if (!isConnected())
    {
        return std::unexpected("[MariaDatabase] No active database connection");
    }

    try
    {
        std::unique_ptr<sql::Statement> stmt(m_Connection->createStatement());
        std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery(query));
        return DBResult(rs.release()); // DBResult takes ownership
    }
    catch (const sql::SQLException &e)
    {
        return std::unexpected(std::string("[MariaDatabase] Query failed: ") + e.what());
    }
}

} // namespace pap
