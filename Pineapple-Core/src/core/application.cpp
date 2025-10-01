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


        m_LayerStack.push_back(std::make_unique<ImGuiLayer>(m_Window->GetNativeWindow()));



    }

    Application::~Application() {
        // Clean up layers in reverse order

        m_LayerStack.clear();
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

			// Main layer update here
			for (const std::unique_ptr<Layer>& layer : m_LayerStack)
				layer->OnUpdate(dt);

			// NOTE: rendering can be done elsewhere (eg. render thread)
			for (const std::unique_ptr<Layer>& layer : m_LayerStack)
				layer->OnRender();

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
