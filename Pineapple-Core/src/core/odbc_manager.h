#pragma once
#include <string>
#include <vector>
#include <nanodbc/nanodbc.h>

namespace pap {

struct ODBCConfig {
    std::string dsn_name;
    std::string driver;
    std::string driver_path;
    std::string server;
    std::string database;
    std::string user;
    std::string password;
    int port = 3306;
};

class ODBCManager {
public:
    ODBCManager(const ODBCConfig& config);
    ~ODBCManager();

    // Create DSN and driver ini files
    bool create_dsn_if_missing();
    bool create_driver_ini_if_missing();

    // Connect once
    bool connect();
    void shutdown();

    // List all databases
    std::vector<std::string> list_databases();
    std::string get_connection_info() const;

    nanodbc::connection& getConnection() { return conn; }
    const nanodbc::connection& getConnection() const { return conn; }


private:
    ODBCConfig config;
    nanodbc::connection conn;
    bool connected = false;
};

}
