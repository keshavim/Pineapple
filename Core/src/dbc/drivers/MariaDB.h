#pragma once
#include "../DBConnector.h"


namespace sql {
    class Connection;
}

namespace pap
{
    class MariaDatabase : public DBConnector
    {
    public:
        MariaDatabase();
        ~MariaDatabase() override;

        Result<void> connect(const std::string &uri,
                             const std::string &user,
                             const std::string &password) override;

        void disconnect() override;
        bool isConnected() const override;


        Result<DBResult> executeQuery(const std::string &query) override;
        Result<void> dryRun(const std::string &query) override;


        Result<void> beginTransaction() override;
        Result<void> commitTransaction() override;
        Result<void> rollbackTransaction() override;

        Result<std::string> getServerVersion() const override;

    private:
        mutable std::mutex m_ConnMutex;
        std::unique_ptr<sql::Connection> m_Connection;
    };
}
