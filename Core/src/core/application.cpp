#include "application.h"
#include "event.h"
#include "pinepch.h"

#include "ImGui/layers/ImGuiDockSpace.h"
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


    imguiManager.init(m_Window->GetNativeWindow());

    pushOverlay<ImGuiDockSpace>();
}

Application::~Application()
{
    // Clean up layers in reverse order
    layerManager.clear();
    imguiManager.shutdown();
    m_Window->Destroy();
}


void Application::OnEvent(Event::Base &e)
{
    imguiManager.onEvent(e);

    PAP_EVENT_DISPATCH(
        Event::KeyPressed,
        e,
        if (e.key == KeyCode::Escape) {
            e.handled = true;
            m_Running = false;
        });

    if (e.getType() == EventType::WindowClosed)
    {
        Stop();
    }

    layerManager.onEvent(e);
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


        layerManager.onUpdate(dt);


        imguiManager.newFrame(dt);

        layerManager.onRender();
        imguiManager.render();


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
