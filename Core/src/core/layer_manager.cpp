#include "layer_manager.h"
#include <algorithm>

namespace pap {

LayerManager::~LayerManager()
{
    clear();
}

void LayerManager::pushLayer(std::unique_ptr<Layer> layer)
{
    m_Layers.insert(m_Layers.begin() + m_OverlayInsertIndex, std::move(layer));
    ++m_OverlayInsertIndex;
}

void LayerManager::pushOverlay(std::unique_ptr<Layer> layer)
{
    m_Layers.push_back(std::move(layer));
}

void LayerManager::onUpdate(float dt)
{
    for (auto& layer : m_Layers)
    {
        if (layer->getState() == LayerState::Active ||
            layer->getState() == LayerState::Hidden)
        {
            layer->onUpdate(dt);
        }
    }
}

void LayerManager::onRender()
{
    // Normal layers
    for (size_t i = 0; i < m_OverlayInsertIndex; ++i)
    {
        auto& layer = m_Layers[i];
        if (layer->getState() != LayerState::Hidden &&
            layer->getState() != LayerState::Deleted)
        {
            layer->onRender();
        }
    }

    // Overlays
    for (size_t i = m_OverlayInsertIndex; i < m_Layers.size(); ++i)
    {
        auto& layer = m_Layers[i];
        if (layer->getState() != LayerState::Hidden &&
            layer->getState() != LayerState::Deleted)
        {
            layer->onRender();
        }
    }

    removeDeletedLayers();
}

void LayerManager::onEvent(Event::Base& e)
{
    for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
    {
        auto& layer = *it;
        if (layer->getState() == LayerState::Deleted)
            continue;

        layer->onEvent(e);
        if (e.handled)
            break;
    }
}

void LayerManager::markLayerForDeletion(Layer* ptr)
{
    for (auto& l : m_Layers)
    {
        if (l.get() == ptr)
        {
            l->setState(LayerState::Deleted);
            break;
        }
    }
}

void LayerManager::clear()
{
    m_Layers.clear();
    m_OverlayInsertIndex = 0;
}

void LayerManager::removeDeletedLayers()
{
    m_Layers.erase(
        std::remove_if(m_Layers.begin(), m_Layers.end(),
            [](const std::unique_ptr<Layer>& layer) {
                return layer->getState() == LayerState::Deleted;
            }),
        m_Layers.end());

    // Recalculate overlay split
    size_t normalCount = 0;
    for (size_t i = 0; i < m_Layers.size(); ++i)
    {
        if (i >= m_OverlayInsertIndex) break;
        ++normalCount;
    }
    m_OverlayInsertIndex = normalCount;
}
} // namespace pap
