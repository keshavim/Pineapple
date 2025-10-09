#pragma once
#include "core/layer.h"
#include "dbc/Manager.h"
#include "dbc/QueryData.h"
#include <optional>
#include <string>
#include <vector>


class DBTableViewerWindow : public pap::Layer
{
public:
    DBTableViewerWindow(const std::string &title, const std::string &schema)
        : m_Title(title), m_Schema(schema), m_Open(true)
    {
    }

    void onRender() override;
    bool wantsCapture() const override
    {
        return true;
    }
    void onEvent(pap::Event::Base &e) override
    {
    }

private:
    std::string m_Title;
    std::string m_Schema;
    bool m_Open;

    // Cached data to avoid repeated queries every frame
    std::optional<pap::db::QueryData> m_TableData;
    bool m_Queried{false};
};
