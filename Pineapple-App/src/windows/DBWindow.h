// db_window.h
#ifndef DB_WINDOW_H
#define DB_WINDOW_H

#include <memory>
#include <string>
#include <imgui.h>
#include "ImGui/ImGuiWindow.h"
#include "dbc/DBManager.h"
#include "dbc/DBResult.h"
#include <iostream>



class DBWindow : public pap::ImGuiWindow{
public:
    DBWindow(const std::string& title);


    void drawImGui() override;

private:
    std::string m_Title;

    pap::DBResult m_Result;

    //need to make this into wigets
    bool drawTable();
};


#endif
