#pragma once

#include "core/layer.h"
#include "core/event.h"
#include "dbc/Manager.h"
#include <string>


class DBConnectionWindow : public pap::Overlay
{
public:
    explicit DBConnectionWindow(const std::string &title);

    void onImGuiRenderer() override;

private:
    pap::db::Result<void> connectNew();
    pap::db::Result<void> reconnect(const pap::db::ConnectInfo &info);

    std::string m_Title;
    char m_Uri[256] = "";
    char m_User[64] = "";
    char m_Password[64] = "";
    pap::db::Driver m_SelectedDriver = pap::db::Driver::Maria;

    // Map from connection key to LayerManager index of the overlay
    std::unordered_map<std::string, size_t> m_ConnectionWindows;

    static std::string makeKey(const pap::db::ConnectInfo &info)
    {
        return info.user + "@" + info.uri;
    }
};
