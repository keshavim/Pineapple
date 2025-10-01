#include "../pinepch.h"
#include "core/application.h"
#include "ImGuiLayer.h"


#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>



namespace pap {

    ImGuiLayer::ImGuiLayer(GLFWwindow *window)
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
        m_Windows.clear();

    }

    void ImGuiLayer::OnRender() {
        for (auto& window : m_Windows) {
            window->draw();
        }
    }

    void ImGuiLayer::OnUpdate(float ts) {

        for (auto& window : m_Windows) {
            // For now we just let them draw in OnRender.
        }
    }

    void ImGuiLayer::addWindow(std::unique_ptr<ImGuiWindow> window) {
        m_Windows.push_back(std::move(window));
    }

    void ImGuiLayer::removeWindow(const std::string& title) {
        m_Windows.erase(std::remove_if(m_Windows.begin(), m_Windows.end(), [&](const std::unique_ptr<ImGuiWindow>& w) {
            return w->getTitle() == title;
        }), m_Windows.end());
    }


} // namespace pap
