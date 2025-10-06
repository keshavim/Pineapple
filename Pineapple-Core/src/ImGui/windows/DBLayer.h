#pragma once

#include "DBWindow.h"
#include "../ImGuiWindow.h" // Your ImGui layer base
#include "core/core.h"
#include "dbc/DBManager.h"

namespace pap
{


class Database : public pap::ImGuiWindow
{
public:
    Database() : dbWindow("Database Viewer")
    {



        dbWindow.setResult(test.value());
    }

    void drawImGui() override
    {
        dbWindow.draw();
    }

private:
    DBWindow dbWindow;
};
} // namespace pap
