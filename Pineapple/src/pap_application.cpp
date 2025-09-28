#include "pinepch.h"
#include "pap_application.h"


namespace pap {

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;
    }

    Application::~Application() {
        // Clean up layers in reverse order
        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
            (*it)->OnDetach();
        }
        m_LayerStack.clear();
    }

    void Application::Init() {
        PAP_PRINT("Application initialized");
    }

    void Application::Update() {
        // Update all layers
        for (auto& layer : m_LayerStack) {
            layer->OnUpdate();
        }
    }

    void Application::Run() {
        Init();

        PAP_PRINT("Application starting main loop");

        while (m_Running) {
            Update();

            // Simple exit condition for demonstration
            // In a real application, this would be handled by events/input
            static int frameCount = 0;
            frameCount++;
            if (frameCount > 10) {
                m_Running = false;
            }
        }

        PAP_PRINT("Application shutting down");
    }

}
