#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "ImGui/ImGuiWindow.h"
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
        if (findLayer<TLayer>(s_Layers) != s_Layers.end())
            return;

        auto newLayer = std::make_unique<TLayer>(std::forward<Args>(args)...);
        newLayer->onAttach();
        s_Layers.push_back(std::move(newLayer));
    }

    // Push a GUI Layer
    template <typename TLayer, typename... Args>
        requires(std::is_base_of_v<ImGuiWindow, TLayer>)
    static void pushGuiWindow(Args &&...args)
    {
        if (findLayer<TLayer>(s_GuiLayers) != s_GuiLayers.end())
            return;

        auto newLayer = std::make_unique<TLayer>(std::forward<Args>(args)...);
        s_GuiLayers.push_back(std::move(newLayer));
    }

    // Pop non-GUI Layer
    template <typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
    static void popLayer()
    {
        auto it = findLayer<TLayer>(s_Layers);
        if (it != s_Layers.end())
        {
            (*it)->onDetach();
            s_Layers.erase(it);
        }
    }

    // Pop GUI Layer
    template <typename TLayer>
        requires(std::is_base_of_v<ImGuiWindow, TLayer>)
    static void popGuiWindow()
    {
        auto it = findLayer<TLayer>(s_GuiLayers);
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

    template <typename LayerType, typename Container>
    static auto findLayer(Container &layers)
    {
        return std::ranges::find_if(layers, [](const auto &layer) {
            return dynamic_cast<LayerType *>(layer.get()) != nullptr;
        });
    }

private:
    static std::vector<std::unique_ptr<Layer>> s_Layers;
    static std::vector<std::unique_ptr<ImGuiWindow>> s_GuiLayers;
};

} // namespace pap
