#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include <string>
#include <functional>

#include "ImGuiWindow.h"
#include "imGui/ImGuiLayer.h"


namespace pap {
// Manager class that initializes ImGui and draws all registered windows
class ImGuiManager {
public:
    ImGuiManager() = default;
    ~ImGuiManager() = default;

    // Setup ImGui context, style, backends, etc.
    static void Setup(GLFWwindow *window);
    static void Destroy();

    // Starts new ImGui frame (call once per frame before drawing)
    static void NewFrame(float dt);

    // Render all ImGui draw data (call once per frame after drawing)
    static void Render();

    static void AddLayer(std::unique_ptr<ImGuiLayer> layer);


private:
    static std::vector<std::unique_ptr<ImGuiLayer>> m_LayerStack;
};
}
