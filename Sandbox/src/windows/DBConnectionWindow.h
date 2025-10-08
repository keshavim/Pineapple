#pragma once

#include "ImGui/ImGuiWindow.h"
#include "core/event.h"
#include "dbc/DBManager.h"
#include <string>


class DBConnectionWindow : public pap::ImGuiWindow
{
public:
    DBConnectionWindow(const std::string &title);

    void drawImGui() override;
    bool wantsCapture() const override
    {
        return true;
    }
    void onEvent(pap::Event::Base &e) override
    {
    }

private:
    std::string m_Title;

    // Connection form state
    char m_Uri[50] {};
    char m_User[50] {};
    char m_Password[50] {};
    pap::DBDriver m_SelectedDriver = pap::DBDriver::MariaDB;

    void connectNew();
    void reconnect(const pap::ConnectInfo &info);
};
