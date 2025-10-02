#pragma once
#include <GLFW/glfw3.h>


namespace pap{

class Renderer{
public:
    static void Init(GLFWwindow *window);
    static void Destroy();

    static void BeginImGuiFrame();
    static void RenderImGuiFrame();

};


}
