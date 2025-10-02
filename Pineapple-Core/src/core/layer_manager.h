#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include <string>
#include <functional>

#include "layer.h"


namespace pap {
// Manager class that initializes ImGui and draws all registered windows

class LayerManager {
public:
    LayerManager() = delete;

    template<typename TLayer, typename... Args>
    requires(std::is_base_of_v<Layer, TLayer>)
    static void pushLayer(Args&&... args) {
        // Prevent duplicates of the same type
        auto it = std::ranges::find_if(s_Layers.begin(), s_Layers.end(),
            [](const std::unique_ptr<Layer>& layer) {
                return dynamic_cast<TLayer*>(layer.get()) != nullptr;
            });
        if (it != s_Layers.end())
            return; // Already exists, skip

        auto newLayer = std::make_unique<TLayer>(std::forward<Args>(args)...);
        newLayer->onAttach();
        s_Layers.push_back(std::move(newLayer));
    }


    template<typename TLayer>
    requires(std::is_base_of_v<Layer, TLayer>)
    static void popLayer() {
        auto it = std::ranges::find_if(s_Layers.begin(), s_Layers.end(),
            [](const std::unique_ptr<Layer>& layer) {
                return dynamic_cast<TLayer*>(layer.get()) != nullptr;
            });

        if (it != s_Layers.end()) {
            (*it)->onDetach();
            s_Layers.erase(it);
        }
    }

    static void updateAll(float dt);
    static void renderAll();
    static void clearAll();

private:
    static std::vector<std::unique_ptr<Layer>> s_Layers;
};
}
