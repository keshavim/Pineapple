#pragma once


namespace pap
{

class RendererContext
{
public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
};


} // namespace pap
