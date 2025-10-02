#include "pinepch.h"
#include "application.h"

#include "print.h"
#include "layer_manager.h"
#include "ImGui/ImGuiDockSpaceLayer.h"



#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>
#include <thread>

namespace pap {

    Application* Application::s_Instance = nullptr;

    Application::Application(const AppSpecifications& specs)
    :m_Specifications(specs)
     {
        s_Instance = this;

        glfwSetErrorCallback([](int error, const char* description){
            PAP_ERROR("[GLFW Error] ({}): {}", error, description);
        });
        glfwInit();


        m_Window = std::make_shared<Window>(m_Specifications.winSpec);
        m_Window->Create();


        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_Window->GetNativeWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 460");

        LayerManager::pushGuiLayer<ImGuiDockSpaceLayer>();


    }

    Application::~Application() {
        // Clean up layers in reverse order
        LayerManager::clear();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();


        m_Window->Destroy();

    }


    void Application::Update() {
        // Update all layers

    }

    void Application::Run() {

        PAP_PRINT("Application starting main loop");

        m_Running = true;

		float lastTime = GetTime();
        while (m_Running) {



            glfwPollEvents();

			if (m_Window->ShouldClose())
			{
				Stop();
				break;
			}

            float currentTime = GetTime();
			float dt = std::clamp(currentTime - lastTime, 0.001f, 0.1f);
			lastTime = currentTime;


            LayerManager::updateLayers(dt);

            LayerManager::renderLayers();


            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            LayerManager::drawGuiLayers();

            ImGui::Render();
            auto [x,y] = GetFramebufferSize();
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



            m_Window->Update();
        }

        PAP_PRINT("Application shutting down");

    }

    void Application::Stop()
	{
		m_Running = false;
	}

    Application& Application::Get()
	{
		assert(s_Instance);
		return *s_Instance;
	}

    float Application::GetTime()
	{
		return (float)glfwGetTime();
	}

}
