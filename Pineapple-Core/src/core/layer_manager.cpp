#include "pinepch.h"
#include "layer_manager.h"
#include "application.h"


#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

namespace pap {



std::vector<std::unique_ptr<Layer>> LayerManager::s_Layers;

void LayerManager::updateAll(float dt) {
    for (auto& layer : s_Layers)
        layer->onUpdate(dt);
}

void LayerManager::renderAll() {
    for (auto& layer : s_Layers)
        layer->onRender();
}

void LayerManager::clearAll() {
    for (auto& layer : s_Layers)
        layer->onDetach();
    s_Layers.clear();
}





}
