#include "application.h"
#include "event.h"
#include "pinepch.h"

#include "ImGui/ImGuiDockSpaceLayer.h"
#include "core.h"
#include "layer_manager.h"

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
    m_Window->SetEventCallback([this](Event::Base &e) { this->OnEvent(e); });
    m_Window->Create();


    Renderer::Init(m_Window->GetNativeWindow());

    pushGuiWindow<ImGuiDockSpace>();
}

Application::~Application()
{
    // Clean up layers in reverse order
    layerManager.clear();
    Renderer::Destroy();
    m_Window->Destroy();
}


void Application::Update()
{
    // Update all layers
}

void Application::OnEvent(Event::Base &e)
{
    if (e.getType() == EventType::KeyPressed)
    {
        auto key = static_cast<const Event::KeyPressed &>(e);
        if (key.key == GLFW_KEY_ESCAPE)
            Stop();


    }

    PAP_EVENT_DISPATCH(Event::KeyPressed, e,
        if (e.key == GLFW_KEY_ESCAPE) {
            e.handled = true;
            m_Running = false;
        }
    );


    if (e.getType() == EventType::WindowClosed)
    {
        Stop();
    }

    layerManager.OnEvent(e);
}

void Application::Run()
{

    PAP_PRINT("Application starting main loop");

    m_Running = true;

    float lastTime = GetTime();
    while (m_Running)
    {


        glfwPollEvents();


        if (!m_Running)
        {
            break;
        }

        float currentTime = GetTime();
        float dt = std::clamp(currentTime - lastTime, 0.001f, 0.1f);
        lastTime = currentTime;


        layerManager.OnUpdate(dt);

        layerManager.OnRender();


        Renderer::BeginImGuiFrame();

        layerManager.drawImGuiWindows();
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
