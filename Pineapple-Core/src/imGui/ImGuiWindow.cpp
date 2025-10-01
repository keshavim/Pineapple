#include "pinepch.h"
#include "ImGuiWindow.h"
#include "imgui.h"


namespace pap {

    ImGuiWindow::ImGuiWindow(const std::string& title) : m_Title(title) {}

    ImGuiWindow::~ImGuiWindow(){
        m_Elements.clear();
    }

    // Add UI elements
    void ImGuiWindow::addText(const std::string& text) {
        m_Elements.push_back([=](){ ImGui::Text("%s", text.c_str()); });
    }

    void ImGuiWindow::addButton(const std::string& label, std::function<void()> onClick) {
        m_Elements.push_back([=](){
            if (ImGui::Button(label.c_str())) onClick();
        });
    }

    void ImGuiWindow::IsDemoWindow() {
        isDemo = true;
    }

    // Draw the window
    void ImGuiWindow::draw() {

        if(isDemo){
            ImGui::ShowDemoWindow();
            return;
        }

        if (ImGui::Begin(m_Title.c_str())) {
            for (auto& elem : m_Elements) {
                elem();
            }
        }
        ImGui::End();
    }

}
