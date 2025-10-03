#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "ImGui/ImGuiLayer.h"
#include "layer.h"


namespace pap
{

class Application; // friend

class LayerManager
{
public:
    LayerManager() = delete;

    // Push a non-GUI Layer
    template <typename TLayer, typename... Args>
        requires(std::is_base_of_v<Layer, TLayer>)
    static void pushLayer(Args &&...args)
    {
        // Prevent duplicates
        auto it = std::ranges::find_if(s_Layers.begin(), s_Layers.end(), [](const std::unique_ptr<Layer> &layer) {
            return dynamic_cast<TLayer *>(layer.get()) != nullptr;
        });
        if (it != s_Layers.end())
            return;

        auto newLayer = std::make_unique<TLayer>(std::forward<Args>(args)...);
        newLayer->onAttach();
        s_Layers.push_back(std::move(newLayer));
    }

    // Push a GUI Layer
    template <typename TLayer, typename... Args>
        requires(std::is_base_of_v<ImGuiLayer, TLayer>)
    static void pushGuiLayer(Args &&...args)
    {
        auto it =
            std::ranges::find_if(s_GuiLayers.begin(), s_GuiLayers.end(), [](const std::unique_ptr<ImGuiLayer> &layer) {
                return dynamic_cast<TLayer *>(layer.get()) != nullptr;
            });
        if (it != s_GuiLayers.end())
            return;

        auto newLayer = std::make_unique<TLayer>(std::forward<Args>(args)...);
        s_GuiLayers.push_back(std::move(newLayer));
    }

    // Pop non-GUI layer
    template <typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
    static void popLayer()
    {
        auto it = std::ranges::find_if(s_Layers.begin(), s_Layers.end(), [](const std::unique_ptr<Layer> &layer) {
            return dynamic_cast<TLayer *>(layer.get()) != nullptr;
        });
        if (it != s_Layers.end())
        {
            (*it)->onDetach();
            s_Layers.erase(it);
        }
    }

    // Pop GUI layer
    template <typename TLayer>
        requires(std::is_base_of_v<ImGuiLayer, TLayer>)
    static void popGuiLayer()
    {
        auto it =
            std::ranges::find_if(s_GuiLayers.begin(), s_GuiLayers.end(), [](const std::unique_ptr<ImGuiLayer> &layer) {
                return dynamic_cast<TLayer *>(layer.get()) != nullptr;
            });
        if (it != s_GuiLayers.end())
        {
            s_GuiLayers.erase(it);
        }
    }

private:
    friend class Application;

    static void updateLayers(float dt);
    static void renderLayers();
    static void drawGuiLayers();
    static void clear();

private:
    static std::vector<std::unique_ptr<Layer>> s_Layers;
    static std::vector<std::unique_ptr<ImGuiLayer>> s_GuiLayers;
};

} // namespace pap
