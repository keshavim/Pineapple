#pragma once


#include "ImGui/ImGuiWindow.h"
#include "dbc/DBConnector.h"
#include <string>

class DBSchemaBrowserWindow : public pap::ImGuiWindow
{
public:
    DBSchemaBrowserWindow(const std::string& title);

    void drawImGui() override;
    bool wantsCapture() const override { return true; }
    void onEvent(pap::Event::Base& e) override {}

private:
    std::string m_Title;

    // Cached data
    std::vector<std::string> m_Schemas;
    std::optional<std::string> m_SelectedSchema;
    std::vector<pap::TableInfo> m_Tables;

    void refreshSchemas();
    void refreshTables(const std::string& schema);
};
