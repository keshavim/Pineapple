#pragma once
#include "core/layer.h"
#include <GLFW/glfw3.h>


// Dear ImGui forward-decls
struct ImGuiContext;

namespace pap {

class ImGuiDockSpaceLayer : public Layer {
public:
    ImGuiDockSpaceLayer();
    ~ImGuiDockSpaceLayer() override;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(float dt) override;
    void onRender() override;
};

}
