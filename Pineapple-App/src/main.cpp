#include <pineapple.h>

#include "imgui.h"


class DemoWindow : public pap::Layer {
public:
    DemoWindow() : Layer("ImGuiLayer") {}

    void onRender() override {
        ImGui::ShowDemoWindow();

    }
};




void pap::InitApplication(){

   pap::LayerManager::pushLayer<DemoWindow>();

}
