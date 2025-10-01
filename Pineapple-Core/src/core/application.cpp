#include "pinepch.h"
#include "application.h"

#include "print.h"
#include "imGui/ImGuiLayer.h"



#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>
#include <thread>

static void GLFWErrorCallback(int error, const char* description) {
    PAP_ERROR("[GLFW Error] ({}): {}", error, description);
}




namespace pap {

    Application* Application::s_Instance = nullptr;

    Application::Application(const AppSpecifications& specs)
    :m_Specifications(specs)
     {
        s_Instance = this;

        glfwSetErrorCallback(GLFWErrorCallback);
        glfwInit();


        m_Window = std::make_shared<Window>(m_Specifications.winSpec);
        m_Window->Create();


        ImGuiManager::Setup(m_Window->GetNativeWindow());

        // Create a new ImGuiLayer
        auto layer = std::make_unique<ImGuiLayer>(m_Window->GetNativeWindow());

        // Create a new ImGuiWindow (builder)
        auto demoWin = std::make_unique<ImGuiWindow>("Demo Window");
        demoWin->IsDemoWindow();  // add the built-in ImGui demo

        // Add the window to the layer
        layer->addWindow(std::move(demoWin));

        // Push the layer into the manager
        ImGuiManager::AddLayer(std::move(layer));
    }

    Application::~Application() {
        // Clean up layers in reverse order
        ImGuiManager::Destroy();
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

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glfwPollEvents();

			if (m_Window->ShouldClose())
			{
				Stop();
				break;
			}

            float currentTime = GetTime();
			float dt = std::clamp(currentTime - lastTime, 0.001f, 0.1f);
			lastTime = currentTime;

            ImGuiManager::NewFrame(dt);

            ImGuiManager::Render();

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
