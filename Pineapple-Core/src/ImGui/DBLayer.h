#pragma once

#include "dbc/DBManager.h"
#include "DBWindow.h"
#include "ImGuiLayer.h"  // Your ImGui layer base
#include "core/print.h"

namespace pap {


class DatabaseLayer : public pap::ImGuiLayer {
public:
    DatabaseLayer()
        : dbWindow("Database Viewer")
    {
        // Connect to DB
        //authentication will be handled in gui later
        std::string user;
        std::cout << "user: ";
        std::getline(std::cin, user);

        std::string password;
        std::cout << "password: ";
        std::getline(std::cin, password);

        bool ok = dbManager.connect(DBDriver::MariaDB, "tcp://127.0.0.1:3306", user, password, "students");
        PAP_INFO("connected");
        if (ok) {
            std::cout << "[DEBUG] Running query: SELECT * FROM student_info;" << std::endl;
            DBResult test = dbManager.executeQuery("SELECT * FROM student_info;");
            std::cout << test << std::endl;

            dbWindow.setResult(test);
        }
    }

    void drawImGui() override {
        dbWindow.draw();
    }

private:
    DBManager dbManager;
    DBWindow dbWindow;
};
}
