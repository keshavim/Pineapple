#include "layer_manager.h"

namespace pap
{

// Define static members
std::vector<std::unique_ptr<Layer>> LayerManager::s_Layers;
std::vector<std::unique_ptr<ImGuiLayer>> LayerManager::s_GuiLayers;

// Update/render non-GUI layers
void LayerManager::updateLayers(float dt)
{
    for (auto &layer : s_Layers)
        layer->onUpdate(dt);
}

void LayerManager::renderLayers()
{
    for (auto &layer : s_Layers)
        layer->onRender();
}

// Draw GUI layers inside ImGui frame
void LayerManager::drawGuiLayers()
{
    for (auto &layer : s_GuiLayers)
        layer->drawImGui();
}

void LayerManager::clear()
{
    s_GuiLayers.clear();
    s_Layers.clear();
}

} // namespace pap
