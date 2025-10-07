#include "layer_manager.h"

namespace pap
{

// Update/render non-GUI layers
void LayerManager::OnUpdate(float dt)
{
    for (auto &layer : m_Layers)
        layer->OnUpdate(dt);
}

void LayerManager::OnRender()
{
    for (auto &layer : m_Layers)
        layer->OnRender();
}

// Draw GUI layers inside ImGui frame
void LayerManager::drawImGuiWindows()
{
    for (auto &window : m_ImGuiWindows)
        window->drawImGui();
}

void LayerManager::OnEvent(Event::Base &e)
{
    // 1️⃣ First, let ImGui windows handle events if they want to
    for (auto &window : m_ImGuiWindows)
    {
        window->onEvent(e);
        if (window->wantsCapture())
        {
            e.handled = true; // block lower layers
            break;
        }
    }

    // 2️⃣ Then propagate to layers if event not handled
    if (!e.handled)
    {
        for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
        {
            (*it)->OnEvent(e);
            if (e.handled)
                break;
        }
    }
}

void LayerManager::clear()
{
    m_ImGuiWindows.clear();
    m_Layers.clear();
}

} // namespace pap
