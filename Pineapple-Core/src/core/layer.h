#pragma once
#include <string>

namespace pap
{

class Layer
{
public:
    virtual ~Layer() = default;
    virtual void onAttach()
    {
    }
    virtual void onDetach()
    {
    }
    virtual void onUpdate(float dt)
    {
    }
    virtual void onRender()
    {
    }
};


} // namespace pap
