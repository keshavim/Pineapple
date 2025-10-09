#pragma once
#include "layer.h"
#include <concepts>
#include <memory>
#include <vector>

namespace pap
{



class LayerManager
{
public:
    LayerManager() = default;
    ~LayerManager();

    // --- Push layer before overlays ---
    void pushLayer(std::unique_ptr<Layer> layer);
    void pushOverlay(std::unique_ptr<Layer> layer);

    // --- Frame operations ---
    void onUpdate(float dt);
    void onRender();
    void onEvent(Event::Base &e);

    // --- Layer control ---
    void markLayerForDeletion(Layer *ptr);
    void clear();

private:
    void removeDeletedLayers();

private:
    std::vector<std::unique_ptr<Layer>> m_Layers;
    size_t m_OverlayInsertIndex = 0;
};

} // namespace pap
