#include "application.h"
#include "ImGui/DBLayer.h"
#include "pinepch.h"

#include "ImGui/ImGuiDockSpaceLayer.h"
#include "layer_manager.h"
#include "core.h"

#include "renderer/renderer.h"


#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <thread>

namespace pap
{

Application *Application::s_Instance = nullptr;

Application::Application(const AppSpecifications &specs) : m_Specifications(specs)
{
    s_Instance = this;

    glfwSetErrorCallback(
        [](int error, const char *description) { PAP_ERROR("[GLFW Error] ({}): {}", error, description); });
    glfwInit();


    m_Window = std::make_shared<Window>(m_Specifications.winSpec);
    m_Window->Create();

    Renderer::Init(m_Window->GetNativeWindow());

    LayerManager::pushGuiLayer<ImGuiDockSpaceLayer>();
    LayerManager::pushGuiLayer<DatabaseLayer>();
}

Application::~Application()
{
    // Clean up layers in reverse order
    LayerManager::clear();
    Renderer::Destroy();
    m_Window->Destroy();
}


void Application::Update()
{
    // Update all layers
}

void Application::Run()
{

    PAP_PRINT("Application starting main loop");

    m_Running = true;

    float lastTime = GetTime();
    while (m_Running)
    {


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


        Renderer::BeginImGuiFrame();

        LayerManager::drawGuiLayers();
        Renderer::RenderImGuiFrame();


        m_Window->Update();
    }

    PAP_PRINT("Application shutting down");
}

void Application::Stop()
{
    m_Running = false;
}

Application &Application::Get()
{
    assert(s_Instance);
    return *s_Instance;
}

float Application::GetTime()
{
    return (float)glfwGetTime();
}

} // namespace pap
