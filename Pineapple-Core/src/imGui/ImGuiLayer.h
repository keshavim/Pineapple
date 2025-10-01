#pragma once

#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

#include "ImGuiWindow.h"
#include "core/layer.h"

namespace pap {

    class ImGuiLayer : public Layer{
    public:
        ImGuiLayer(GLFWwindow *window);
        ~ImGuiLayer();


        virtual void OnRender() override;
        virtual void OnUpdate(float ts) override;

        // Adds a new window to the internal list
        void addWindow(std::unique_ptr<ImGuiWindow> window);

        // Removes a window by title (optional convenience)
        void removeWindow(const std::string& title);

    private:
        std::vector<std::unique_ptr<ImGuiWindow>> m_Windows;


    };

}
