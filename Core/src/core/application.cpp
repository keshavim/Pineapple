
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "pinepch.h"
#include "core.h"


#include "application.h"
#include "event.h"

#include "ImGui/layers/ImGuiDockSpace.h"
#include "layer_manager.h"
#include <glad/glad.h>

#include "backends/GLFW/GLFW_Window.h"
#include "backends/GLFW/GLFW_Input.h"


namespace pap
{

void Application::Init(const AppSpecifications &specs)
{
    s_Specifications = specs;

    glfwSetErrorCallback(
        [](int error, const char *description) { PAP_ERROR("[GLFW Error] ({}): {}", error, description); });
    glfwInit();

    s_Window = std::make_shared<GLFWWindowBackend>(s_Specifications.winSpec);
    //sents the event function to the window so application can recive its events
    s_Window->SetEventCallback([](Event::Base &e) { Application::OnEvent(e); });
    s_Window->Create();


    s_ImGuiManager.init(*s_Window);

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

    Input::s_Instance->OnEvent(e);

    s_ImGuiManager.onEvent(e);

    PAP_EVENT_DISPATCH(Event::KeyPressed, e, {
        if (e.key == KeyCode::Escape)
        {
            e.handled = true;
            Stop();
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
        if (!s_Running)
            break;

        float currentTime = GetTime();
        float dt = std::clamp(currentTime - lastTime, 0.001f, 0.1f);
        lastTime = currentTime;


        s_LayerManager.onUpdate(dt);


        auto [x,y] = GetFramebufferSize();
        glViewport(0,0,x,y);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        s_ImGuiManager.newFrame(dt);



        s_LayerManager.onRender();
        s_LayerManager.onImGuiRenderer();


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
