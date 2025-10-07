// db_window.h
#ifndef DB_WINDOW_H
#define DB_WINDOW_H

#include "ImGui/ImGuiWindow.h"
#include "dbc/DBManager.h"
#include "dbc/DBResult.h"
#include <imgui.h>
#include <iostream>
#include <memory>
#include <string>
#include "ImGui/widgets/Table.h"


class DBWindow : public pap::ImGuiWindow
{
public:
    DBWindow(const std::string &title);


    void drawImGui() override;

private:
    std::string m_Title;

    pap::DBResult m_Result;

    pap::widgets::Table m_Table;
};


#endif
