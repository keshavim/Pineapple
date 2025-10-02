#pragma once
#include <string>


namespace pap {

// Base for GUI layers
class ImGuiLayer {
public:
    virtual ~ImGuiLayer() = default;
    virtual void drawImGui() = 0; // pure virtual
};

}  // namespace Pineapple
