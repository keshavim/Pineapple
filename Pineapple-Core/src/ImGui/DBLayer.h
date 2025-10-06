#pragma once

#include "dbc/DBManager.h"
#include "DBWindow.h"
#include "ImGuiLayer.h"  // Your ImGui layer base
#include "core/core.h"

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

        auto ok = dbManager.connect(DBDriver::MariaDB, "tcp://127.0.0.1:3306", user, password, "students");

        //todo: make gui
        if(!ok){
            PAP_INFO("failed");
            return;
        }
        std::cout << "[DEBUG] Running query: SELECT * FROM student_info;" << std::endl;
        auto test = dbManager.executeQuery("SELECT * FROM student_info;");
        if(!test){
            std::cout << "aFailed query: " << test.error() << "\n";
        }


        dbWindow.setResult(test.value());
    }

    void drawImGui() override {
        dbWindow.draw();
    }

private:
    DBManager dbManager;
    DBWindow dbWindow;
};
}
