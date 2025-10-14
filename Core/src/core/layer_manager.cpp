#include "layer_manager.h"
#include <algorithm>
#include <cassert>

namespace pap
{

LayerManager::~LayerManager()
{
    clear();
}

size_t LayerManager::pushLayer(std::unique_ptr<Layer> layer)
{
    if (!layer) return -1;

    m_Layers.insert(m_Layers.begin() + m_OverlayIndex, std::move(layer));
    return m_OverlayIndex++; // return index of inserted layer
}

size_t LayerManager::pushOverlay(std::unique_ptr<Layer> overlay)
{
    if (!overlay) return -1;

    m_Layers.push_back(std::move(overlay));
    return m_Layers.size() - 1; // return index of inserted overlay
}

LayerState LayerManager::getState(size_t index) const
{
    assert(index < m_Layers.size());
    return m_Layers[index]->getState();
}

void LayerManager::setState(size_t index, LayerState state)
{
    if (index < m_Layers.size())
        m_Layers[index]->setState(state);
}

void LayerManager::onUpdate(float dt)
{
    for (auto &ptr : m_Layers)
    {
        if (!ptr) continue;
        auto state = ptr->getState();
        if (state == LayerState::Active || state == LayerState::Hidden)
            ptr->onUpdate(dt);
    }
}

void LayerManager::onRender()
{
    for (size_t i = 0; i < m_Layers.size(); ++i)
    {
        auto &ptr = m_Layers[i];
        if (!ptr) continue;
        auto state = ptr->getState();
        if (state == LayerState::Hidden || state == LayerState::Deleted)
            continue;

        ptr->onRender();

    }
}

void LayerManager::onImGuiRenderer()
{
    for (size_t i = 0; i < m_Layers.size(); ++i)
    {
        auto &ptr = m_Layers[i];
        if (!ptr) continue;
        auto state = ptr->getState();
        if (state != LayerState::Hidden && state != LayerState::Deleted)
            ptr->onImGuiRenderer();
    }


}

void LayerManager::onEvent(Event::Base &e)
{
    for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
    {
        auto &ptr = *it;
        if (!ptr) continue;
        if (ptr->getState() == LayerState::Deleted) continue;
        ptr->onEvent(e);
        if (e.handled) return;
    }
}

void LayerManager::clear()
{
    m_Layers.clear();
    m_OverlayIndex = 0;
}

} // namespace pap
