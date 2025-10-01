#pragma once

#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

#include "ImGuiWindow.h"

namespace pap {

    class ImGuiLayer{
    public:
        ImGuiLayer(GLFWwindow *window);
        ~ImGuiLayer();


        void OnRender();
        void OnUpdate(float ts);

        // Adds a new window to the internal list
        void addWindow(std::unique_ptr<ImGuiWindow> window);

        // Removes a window by title (optional convenience)
        void removeWindow(const std::string& title);

    private:
        std::vector<std::unique_ptr<ImGuiWindow>> m_Windows;


    };

}
