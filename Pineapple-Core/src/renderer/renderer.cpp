#include "renderer.h"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include "core/application.h"

namespace pap{


    void Renderer::Init(GLFWwindow *window){
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");
    }
    void Renderer::Destroy(){
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Renderer::BeginImGuiFrame(){
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

    }
    void Renderer::RenderImGuiFrame(){
        ImGui::Render();
        auto [x,y] = Application::Get().GetFramebufferSize();
        glViewport(0, 0, x, y);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup);
        }
    }

}
