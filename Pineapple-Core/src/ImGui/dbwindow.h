// db_window.h
#ifndef DB_WINDOW_H
#define DB_WINDOW_H

#include <memory>
#include <string>
#include <imgui.h>
#include "db_tableview.h"

namespace pap {


class DBWindow {
public:
    DBWindow(const std::string& title)
        : m_Title(title) {}

    void setResult(const DBResult& res) {
        m_Component = std::make_unique<DBResultViewComponent>(res);
    }

    void draw() {
        ImGui::Begin(m_Title.c_str());
        if (m_Component)
            m_Component->draw();
        else
            ImGui::TextUnformatted("No data loaded yet.");
        ImGui::End();
    }

private:
    std::string m_Title;
    std::unique_ptr<DBResultViewComponent> m_Component;
};
}
#endif
