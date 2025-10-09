#include "MariaDB.h"
#include "../QueryData.h"
#include "conncpp/Driver.hpp"
#include "conncpp/Exception.hpp"
#include "conncpp/Statement.hpp"
#include "pinepch.h"

namespace pap
{

namespace db
{
MariaDatabase::MariaDatabase() = default;

MariaDatabase::~MariaDatabase()
{
    disconnect();
}

Result<void> MariaDatabase::connect(const ConnectInfo &info)
{
    try
    {
        sql::Driver *driver = sql::mariadb::get_driver_instance();
        assert(driver);

        m_Connection.reset(driver->connect(info.uri, info.user, info.password));
        assert(m_Connection);
    }
    catch (const sql::SQLException &e)
    {
        return std::unexpected(Error{ErrorCode::ConnectionFailed, e.what()});
    }

    return {};
}

void MariaDatabase::disconnect()
{
    if (m_Connection)
    {
        m_Connection->close();
        m_Connection.reset();
    }
}

bool MariaDatabase::isConnected() const
{
    return m_Connection && m_Connection->isValid();
}

Result<QueryData> MariaDatabase::executeQuery(const std::string &query)
{
    if (!m_Connection)
        return std::unexpected(Error{ErrorCode::NoConnection});

    try
    {
        std::unique_ptr<sql::Statement> stmt(m_Connection->createStatement());
        std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery(query.c_str()));

        return QueryData(rs.get());
    }
    catch (const sql::SQLException &e)
    {
        return std::unexpected(Error{ErrorCode::QueryFailed, e.what()});
    }
}

Result<void> MariaDatabase::dryRun(const std::string &query)
{
    auto res = executeQuery("EXPLAIN " + query);
    if (!res)
        return std::unexpected(res.error());
    return {};
}

Result<void> MariaDatabase::beginTransaction()
{
    if (!m_Connection)
        return std::unexpected(Error{ErrorCode::NoConnection});
    m_Connection->setAutoCommit(false);
    return {};
}

Result<void> MariaDatabase::commitTransaction()
{
    if (!m_Connection)
        return std::unexpected(Error{ErrorCode::NoConnection});
    m_Connection->commit();
    m_Connection->setAutoCommit(true);
    return {};
}

Result<void> MariaDatabase::rollbackTransaction()
{
    if (!m_Connection)
        return std::unexpected(Error{ErrorCode::NoConnection});
    m_Connection->rollback();
    m_Connection->setAutoCommit(true);
    return {};
}
} // namespace db
} // namespace pap
