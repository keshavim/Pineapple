#pragma once
#include "core/event.h"
#include <string>

namespace pap
{

class Layer
{
public:
    virtual ~Layer() = default;
    virtual void OnAttach()
    {
    }
    virtual void OnDetach()
    {
    }
    virtual void OnUpdate(float dt)
    {
    }
    virtual void OnRender()
    {
    }
    virtual void OnEvent(Event::Base &e)
    {
    }
};


} // namespace pap
