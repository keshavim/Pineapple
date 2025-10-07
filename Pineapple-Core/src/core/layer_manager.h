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
    LayerManager() = default;

    // Push a non-GUI Layer
    template <std::derived_from<Layer> TLayer, typename... Args>
    void pushLayer(Args &&...args)
    {
        if (findLayer<TLayer>(m_Layers) != m_Layers.end())
            return;

        auto newLayer = std::make_unique<TLayer>(std::forward<Args>(args)...);
        newLayer->onAttach();
        m_Layers.push_back(std::move(newLayer));
    }

    // Push a GUI Layer
    template <std::derived_from<ImGuiWindow> TLayer, typename... Args>
    void pushGuiWindow(Args &&...args)
    {
        if (findLayer<TLayer>(m_ImGuiWindows) != m_ImGuiWindows.end())
            return;

        auto newLayer = std::make_unique<TLayer>(std::forward<Args>(args)...);
        m_ImGuiWindows.push_back(std::move(newLayer));
    }

    // Pop non-GUI Layer
    template <std::derived_from<Layer> TLayer>
    void popLayer()
    {
        auto it = findLayer<TLayer>(m_Layers);
        if (it != m_Layers.end())
        {
            (*it)->onDetach();
            m_Layers.erase(it);
        }
    }

    // Pop GUI Layer
    template <std::derived_from<ImGuiWindow>, typename TLayer>
    void popGuiWindow()
    {
        auto it = findLayer<TLayer>(m_ImGuiWindows);
        if (it != m_ImGuiWindows.end())
        {
            m_ImGuiWindows.erase(it);
        }
    }


private:
    friend class Application;

    void OnUpdate(float dt);
    void OnRender();
    void OnEvent(Event::Base &e);
    void drawImGuiWindows();
    void clear();

    template <typename LayerType, typename Container>
    auto findLayer(Container &layers)
    {
        return std::ranges::find_if(layers, [](const auto &layer) {
            return dynamic_cast<LayerType *>(layer.get()) != nullptr;
        });
    }

private:
    std::vector<std::unique_ptr<Layer>> m_Layers;
    std::vector<std::unique_ptr<ImGuiWindow>> m_ImGuiWindows;
};

} // namespace pap
