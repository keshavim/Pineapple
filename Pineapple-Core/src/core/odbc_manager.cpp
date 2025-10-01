#include "pinepch.h"
#include "odbc_manager.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

namespace pap {


// ODBCManager::ODBCManager(const ODBCConfig& cfg) : config(cfg) {}
// ODBCManager::~ODBCManager(){
//     shutdown();
// }

// // -------------------------
// // Create .odbc.ini (DSN)
// // -------------------------
// bool ODBCManager::create_dsn_if_missing() {
// #ifndef _WIN32
//     const char* home = std::getenv("HOME");
//     if (!home) return false;

//     std::string file_path = std::string(home) + "/.odbc.ini";
//     std::ifstream ifs(file_path);
//     if (ifs.good()) return true; // already exists

//     std::ofstream ofs(file_path, std::ios::app);
//     if (!ofs.is_open()) return false;

//     ofs << "[" << config.dsn_name << "]\n";
//     ofs << "Driver = " << config.driver << "\n";
//     ofs << "Server = " << config.server << "\n";
//     ofs << "Database = " << config.database << "\n";
//     ofs << "User = " << config.user << "\n";
//     ofs << "Password = " << config.password << "\n";
//     ofs << "Port = " << config.port << "\n";

//     ofs.close();
// #endif
//     return true;
// }

// // -------------------------
// // Create .odbcinst.ini (Driver)
// // -------------------------
// bool ODBCManager::create_driver_ini_if_missing() {
// #ifndef _WIN32
//     const char* home = std::getenv("HOME");
//     if (!home) return false;

//     std::string file_path = std::string(home) + "/.odbcinst.ini";
//     std::ifstream ifs(file_path);
//     if (ifs.good()) return true; // already exists

//     std::ofstream ofs(file_path, std::ios::app);
//     if (!ofs.is_open()) return false;

//     ofs << "[" << config.driver << "]\n";
//     ofs << "Driver = " << config.driver_path << "\n";

//     ofs.close();
// #endif
//     return true;
// }

// // -------------------------
// // Connect once
// // -------------------------
// bool ODBCManager::connect() {
//     if (connected) return true;

//     try {
//         // Use the DSN that you know works via isql
//         std::string connStr =
//             "DSN=MariaDBTest;"
//             "UID=root;"
//             "PWD=jeoYfU*17g#!$B;"
//             "ConnectTimeout=5;"; // optional timeout to prevent stalls

//         conn = nanodbc::connection(connStr); // immediately connects

//         if(!conn.connected()){\
//             std::cerr << "Failled to connect\n";
//             return false;


//         }
//         connected = true;

//         std::cerr << "Connected successfully!\n";
//         return true;
//     } catch (const std::exception& e) {
//         std::cerr << "ODBC Connect failed: " << e.what() << std::endl;
//         connected = false;
//         return false;
//     }
// }

// // -------------------------
// // List all databases
// // -------------------------
// std::vector<std::string> ODBCManager::list_databases() {
//     std::vector<std::string> databases;
//     if (!connect()) return databases;

//     try {
//         nanodbc::result res = nanodbc::execute(
//             conn,
//             "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA;"
//         );

//         while (res.next()) {
//             databases.push_back(res.get<std::string>(0));
//         }

//     } catch (const std::exception& e) {
//         std::cerr << "Query failed: " << e.what() << std::endl;
//     }


//     return databases;
// }

// std::string ODBCManager::get_connection_info() const {
//     std::ostringstream oss;
//     oss << "DSN: " << config.dsn_name << "\n"
//         << "Driver: " << config.driver << "\n"
//         << "Server: " << config.server << "\n"
//         << "Database: " << config.database << "\n"
//         << "User: " << config.user << "\n"
//         << "Port: " << config.port;
//     return oss.str();
// }

// void ODBCManager::shutdown() {
//     if (connected) {
//         try {
//             // Disconnect and reset the connection object
//             conn.disconnect();
//             conn = nanodbc::connection(); // Force destructor/cleanup
//         } catch (const std::exception& e) {
//             std::cerr << "Error during shutdown: " << e.what() << std::endl;
//         }
//         connected = false;
//     }
// }

}
