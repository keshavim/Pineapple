#pragma once
#include "ImGui/ImGuiManager.h"
#include "core/event.h"
#include "layer.h"
#include <memory>
#include <vector>

namespace pap
{

class LayerManager
{
public:
    LayerManager() = default;
    ~LayerManager();

    // --- Push ---
    size_t pushLayer(std::unique_ptr<Layer> layer);      // inserts before overlay
    size_t pushOverlay(std::unique_ptr<Layer> overlay);  // inserts after normal layers

    // --- Frame operations ---
    void onUpdate(float dt);
    void onRender();
    void onImGuiRenderer();
    void onEvent(Event::Base &e);

    // --- State access ---
    LayerState getState(size_t index) const;
    void setState(size_t index, LayerState state);

    // --- Layer control ---
    void clear();

private:
    std::vector<std::unique_ptr<Layer>> m_Layers; // all layers
    size_t m_OverlayIndex = 0;                     // split index: 0..m_OverlayIndex-1 = normal layers, m_OverlayIndex..end = overlays
};

} // namespace pap
