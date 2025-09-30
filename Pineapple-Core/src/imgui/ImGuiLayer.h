#pragma once

#include <GLFW/glfw3.h>

#include "pap_layer.h"

namespace pap {

    class ImGuiLayer : public Layer{
        public:
        ImGuiLayer(GLFWwindow *window);
        ~ImGuiLayer();


        void OnRender() override;

        void OnUpdate(float ts) override;
    };

}
