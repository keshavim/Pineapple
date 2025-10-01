#pragma once

#include <GLFW/glfw3.h>
#include <vector>

#include "core/layer.h"

namespace pap {

    class ImGuiLayer : public Layer{
        public:
        ImGuiLayer(GLFWwindow *window);
        ~ImGuiLayer();


        void OnRender() override;
        void OnUpdate(float ts) override;

    };

}
