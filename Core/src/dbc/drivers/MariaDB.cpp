#include "MariaDB.h"
#include "../DBResult.h"
#include "conncpp/Connection.hpp"
#include "conncpp/DatabaseMetaData.hpp"
#include "conncpp/Driver.hpp"
#include "conncpp/Exception.hpp"
#include "conncpp/Statement.hpp"
#include <cassert>

namespace pap
{
    MariaDatabase::MariaDatabase() = default;
    MariaDatabase::~MariaDatabase() { disconnect(); }

    Result<void> MariaDatabase::connect(const std::string &uri,
                                        const std::string &user,
                                        const std::string &password)
    {
        //std::scoped_lock lock(m_ConnMutex);
        try
        {
            sql::Driver* driver = sql::mariadb::get_driver_instance();
            assert(driver);
            m_Connection.reset(driver->connect(uri, user, password));
            assert(m_Connection);
        }
        catch (const sql::SQLException &e)
        {
            return std::unexpected("MariaDB connection failed: " + std::string(e.what()));
        }
        return {};
    }

    void MariaDatabase::disconnect()
    {
        //std::scoped_lock lock(m_ConnMutex);
        if (m_Connection)
        {
            m_Connection->close();
            m_Connection.reset();
        }
    }

    bool MariaDatabase::isConnected() const
    {
        //std::scoped_lock lock(m_ConnMutex);
        return m_Connection && m_Connection->isValid();
    }

    // Result<std::string> MariaDatabase::getCurrentSchema() const
    // {
    //     //std::scoped_lock lock(m_ConnMutex);
    //     if (!m_Connection) return std::unexpected("No connection");
    //     return m_CurrentSchema;
    // }

    // Result<void> MariaDatabase::switchSchema(const std::string &schema)
    // {
    //     //std::scoped_lock lock(m_ConnMutex);
    //     if (!m_Connection) return std::unexpected("No connection");
    //     try { m_Connection->setSchema(schema); m_CurrentSchema = schema; }
    //     catch (const sql::SQLException &e) { return std::unexpected(e.what()); }
    //     return {};
    // }

    Result<DBResult> MariaDatabase::executeQuery(const std::string &query)
    {
        //std::scoped_lock lock(m_ConnMutex);
        if (!m_Connection) return std::unexpected("No connection");

        try
        {
            std::unique_ptr<sql::Statement> stmt(m_Connection->createStatement());
            std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery(query));
            return DBResult(rs.get());
        }
        catch (const sql::SQLException &e) { return std::unexpected(e.what()); }
    }

    Result<void> MariaDatabase::dryRun(const std::string &query)
    {
        // For MariaDB, simulate with EXPLAIN
        auto res = executeQuery("EXPLAIN " + query);
        if (!res) return std::unexpected(res.error());
        return {};
    }

    // Result<std::vector<std::string>> MariaDatabase::listSchemas()
    // {
    //     auto res = executeQuery("SHOW DATABASES;");
    //     if (!res) return std::unexpected(res.error());

    //     std::vector<std::string> schemas;
    //     for (size_t i = 0; i < res->getRowCount(); ++i)
    //     {
    //         auto row = res->getRow(i);
    //         if (!row) return std::unexpected(row.error());
    //         schemas.push_back((*row)[0]);
    //     }
    //     return schemas;
    // }

    // Result<std::vector<TableInfo>> MariaDatabase::listTables(const std::string &schema)
    // {
    //     auto res = executeQuery("SHOW TABLES FROM " + schema + ";");
    //     if (!res) return std::unexpected(res.error());

    //     std::vector<TableInfo> tables;
    //     for (size_t i = 0; i < res->getRowCount(); ++i)
    //     {
    //         auto row = res->getRow(i);
    //         if (!row) return std::unexpected(row.error());
    //         tables.push_back({ (*row)[0], {} });
    //     }
    //     return tables;
    // }

    // Result<TableInfo> MariaDatabase::getTableInfo(const std::string &schema, const std::string &table)
    // {
    //     auto res = executeQuery("SHOW COLUMNS FROM " + schema + "." + table + ";");
    //     if (!res) return std::unexpected(res.error());

    //     TableInfo tinfo;
    //     tinfo.name = table;
    //     for (size_t i = 0; i < res->getRowCount(); ++i)
    //     {
    //         auto row = res->getRow(i);
    //         if (!row) return std::unexpected(row.error());

    //         ColumnInfo col;
    //         col.name = (*row)[0];
    //         col.type = (*row)[1];
    //         col.isNullable = ((*row)[2] == "YES");
    //         col.isPrimaryKey = ((*row)[3] == "PRI");
    //         tinfo.columns.push_back(col);
    //     }
    //     return tinfo;
    // }

    Result<void> MariaDatabase::beginTransaction()
    {
        if (!m_Connection) return std::unexpected("No connection");
        m_Connection->setAutoCommit(false);
        return {};
    }

    Result<void> MariaDatabase::commitTransaction()
    {
        if (!m_Connection) return std::unexpected("No connection");
        m_Connection->commit();
        m_Connection->setAutoCommit(true);
        return {};
    }

    Result<void> MariaDatabase::rollbackTransaction()
    {
        if (!m_Connection) return std::unexpected("No connection");
        m_Connection->rollback();
        m_Connection->setAutoCommit(true);
        return {};
    }

    Result<std::string> MariaDatabase::getServerVersion() const
    {
        if (!m_Connection) return std::unexpected("No connection");
        return m_Connection->getMetaData()->getDatabaseProductVersion().c_str();
    }

    // Result<std::string> MariaDatabase::getConnectionName() const
    // {
    //     if(m_CurrentSchema.empty()){
    //         std::unexpected("No connection");
    //     }
    //     return m_CurrentSchema;
    // }

    std::unique_ptr<DBConnector> createMariaDatabase()
    {
        return std::make_unique<MariaDatabase>();
    }
}
