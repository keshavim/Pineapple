#include "pinepch.h"
#include "pap_application.h"

#include "pap_print.h"
#include "imgui/ImGuiLayer.h"



#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>

static void GLFWErrorCallback(int error, const char* description) {
    PAP_ERROR("[GLFW Error] ({}): {}", error, description);
}

static void Imgui_Init(GLFWwindow * window){
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        // Enable Docking
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;       // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");

}

static void Imgui_Destroy(){
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
}
static void Imgui_Render(){
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();


            // Dockspace example (full window)
            {
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
                const ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->Pos);
                ImGui::SetNextWindowSize(viewport->Size);
                ImGui::SetNextWindowViewport(viewport->ID);
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                ImGui::Begin("DockSpace", nullptr, window_flags);
                ImGui::PopStyleVar(2);

                // DockSpace
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

                // Render demo window inside docking space
                ImGui::ShowDemoWindow();

                ImGui::End();
            }


            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

namespace pap {

    Application* Application::s_Instance = nullptr;

    Application::Application(const AppSpecifications& specs)
    :m_Specifications(specs)
     {
        s_Instance = this;

        glfwSetErrorCallback(GLFWErrorCallback);
        glfwInit();


        m_Window = std::make_unique<Window>(m_Specifications.winSpec);
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
