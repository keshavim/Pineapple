#include <pineapple.h>

#include "imgui.h"


class DemoWindow : public pap::ImGuiLayer {
public:
    DemoWindow() {}

    void drawImGui() override {
        ImGui::ShowDemoWindow();

    }
};




void pap::InitApplication(){

   pap::LayerManager::pushGuiLayer<DemoWindow>();

}
