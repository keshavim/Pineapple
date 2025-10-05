#pragma once

#include "dbc/db_manager.h"
#include "dbwindow.h"
#include "ImGuiLayer.h"  // Your ImGui layer base
#include "core/print.h"

namespace pap {


class DatabaseLayer : public pap::ImGuiLayer {
public:
    DatabaseLayer()
        : dbWindow("Database Viewer")
    {
        // Connect to DB
        bool ok = dbManager.connect("tcp://127.0.0.1:3306", "root", "jeoYfU*17g#!$B", "students");
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
