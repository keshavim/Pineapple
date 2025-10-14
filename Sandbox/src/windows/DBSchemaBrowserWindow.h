#pragma once


#include "core/layer.h"
#include "dbc/Connector.h"
#include "dbc/Schema.h"
#include <string>

class DBSchemaBrowserWindow : public pap::Overlay
{
public:
    DBSchemaBrowserWindow(const std::string &title);

    void onImGuiRenderer() override;

private:
    std::string m_Title;

    // Cached data
    std::vector<std::string> m_Schemas;
    std::optional<std::string> m_SelectedSchema;
    std::vector<pap::db::TableInfo> m_Tables;

    void refreshSchemas();
    void refreshTables(const std::string &schema);
};
