#pragma once


#include <cstdint>
namespace pap
{

enum class RendererAPI : uint32_t
{
    None = 0,
    OpenGL,
};

class Renderer
{
    public:
    static RendererAPI GetAPI(){return s_RendererAPI;}
private:
    static RendererAPI s_RendererAPI;
};

} // namespace pap
