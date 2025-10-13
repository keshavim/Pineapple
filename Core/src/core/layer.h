#pragma once
#include "core/event.h"
#include "imgui.h"


namespace pap
{

// Layer lifecycle states
enum class LayerState
{
    Active,    // Updates + Renders
    Suspended, // Renders last frame, but no updates
    Hidden,    // Updates, but not rendered
    Deleted    // Removed at end of frame
};

// Base interface for all layers
class Layer
{
public:
    Layer() = default;
    virtual ~Layer() = default;

    Layer(const Layer &) = delete;
    Layer &operator=(const Layer &) = delete;

    // --- Core frame functions ---
    virtual void onUpdate(float dt)
    {
    }
    virtual void onRender()
    {
    }
    virtual void onEvent(Event::Base &e)
    {
    }

    // --- State management ---
    void setState(LayerState state)
    {
        m_State = state;
    }
    LayerState getState() const
    {
        return m_State;
    }

    bool isMarkedForDeletion() const
    {
        return m_State == LayerState::Deleted;
    }
private:
    LayerState m_State = LayerState::Active;
};
// Concept for layer types
template <typename T>
concept LayerType = std::derived_from<T, Layer>;
} // namespace pap
