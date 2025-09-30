#include "ODBCManager.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

ODBCManager::ODBCManager(const ODBCConfig& cfg) : config(cfg) {}

// -------------------------
// Create .odbc.ini (DSN)
// -------------------------
bool ODBCManager::create_dsn_if_missing() {
#ifndef _WIN32
    const char* home = std::getenv("HOME");
    if (!home) return false;

    std::string file_path = std::string(home) + "/.odbc.ini";
    std::ifstream ifs(file_path);
    if (ifs.good()) return true; // already exists

    std::ofstream ofs(file_path, std::ios::app);
    if (!ofs.is_open()) return false;

    ofs << "[" << config.dsn_name << "]\n";
    ofs << "Driver = " << config.driver << "\n";
    ofs << "Server = " << config.server << "\n";
    ofs << "Database = " << config.database << "\n";
    ofs << "User = " << config.user << "\n";
    ofs << "Password = " << config.password << "\n";
    ofs << "Port = " << config.port << "\n";

    ofs.close();
#endif
    return true;
}

// -------------------------
// Create .odbcinst.ini (Driver)
// -------------------------
bool ODBCManager::create_driver_ini_if_missing() {
#ifndef _WIN32
    const char* home = std::getenv("HOME");
    if (!home) return false;

    std::string file_path = std::string(home) + "/.odbcinst.ini";
    std::ifstream ifs(file_path);
    if (ifs.good()) return true; // already exists

    std::ofstream ofs(file_path, std::ios::app);
    if (!ofs.is_open()) return false;

    ofs << "[" << config.driver << "]\n";
    ofs << "Driver = " << config.driver_path << "\n";

    ofs.close();
#endif
    return true;
}

// -------------------------
// Connect once
// -------------------------
bool ODBCManager::connect() {
    if (connected) return true;

    try {
        std::string conn_str =
            "DSN=" + config.dsn_name + ";" +
            "UID=" + config.user + ";" +
            "PWD=" + config.password + ";" +
            "PORT=" + std::to_string(config.port) + ";" +
            "CONNECT_TIMEOUT=5;";

        conn = nanodbc::connection(conn_str);
        connected = true;
    } catch (const std::exception& e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
        connected = false;
    }

    return connected;
}

// -------------------------
// List all databases
// -------------------------
std::vector<std::string> ODBCManager::list_databases() {
    std::vector<std::string> databases;
    if (!connect()) return databases;

    try {
        nanodbc::result res = nanodbc::execute(conn, "SHOW DATABASES;");
        while (res.next()) {
            databases.push_back(res.get<std::string>(0));
        }
    } catch (const std::exception& e) {
        std::cerr << "Query failed: " << e.what() << std::endl;
    }

    return databases;
}
