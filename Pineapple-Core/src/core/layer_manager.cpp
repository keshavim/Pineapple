#include "layer_manager.h"

namespace pap
{

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
