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

void Application::Init(const AppSpecifications &specs)
{
    s_Specifications = specs;

    glfwSetErrorCallback([](int error, const char *description) {
        PAP_ERROR("[GLFW Error] ({}): {}", error, description);
    });
    glfwInit();

    s_Window = std::make_shared<Window>(s_Specifications.winSpec);
    s_Window->SetEventCallback([](Event::Base &e) { Application::OnEvent(e); });
    s_Window->Create();

    s_ImGuiManager.init(s_Window->GetNativeWindow());

    PushOverlay<ImGuiDockSpace>();
}

void Application::Shutdown()
{
    s_LayerManager.clear();
    s_ImGuiManager.shutdown();
    if (s_Window)
    {
        s_Window->Destroy();
        s_Window.reset();
    }
    glfwTerminate();
}

void Application::OnEvent(Event::Base &e)
{
    s_ImGuiManager.onEvent(e);

    PAP_EVENT_DISPATCH(Event::KeyPressed, e, {
        if (e.key == KeyCode::Escape) {
            e.handled = true;
            s_Running = false;
        }
    });

    if (e.getType() == EventType::WindowClosed)
    {
        Stop();
    }

    s_LayerManager.onEvent(e);
}

void Application::Run()
{
    PAP_PRINT("Application starting main loop");
    s_Running = true;

    float lastTime = GetTime();
    while (s_Running)
    {
        glfwPollEvents();
        if (!s_Running) break;

        float currentTime = GetTime();
        float dt = std::clamp(currentTime - lastTime, 0.001f, 0.1f);
        lastTime = currentTime;

        s_LayerManager.onUpdate(dt);
        s_LayerManager.onRender();

        s_ImGuiManager.newFrame(dt);
        s_LayerManager.onRenderOverlay();
        s_ImGuiManager.render();

        s_Window->Update();
    }

    PAP_PRINT("Application shutting down");
}

void Application::Stop()
{
    s_Running = false;
}

std::pair<int, int> Application::GetFramebufferSize()
{
    if (s_Window)
        return s_Window->GetFramebufferSize();
    return {0, 0};
}

float Application::GetTime()
{
    return static_cast<float>(glfwGetTime());
}

} // namespace pap
