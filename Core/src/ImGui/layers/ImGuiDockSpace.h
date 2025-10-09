#pragma once
#include "core/layer.h"
#include <GLFW/glfw3.h>


namespace pap
{

class ImGuiDockSpace : public Layer
{
public:
    ImGuiDockSpace();
    ~ImGuiDockSpace() override;

    void onRender() override;
};

} // namespace pap
