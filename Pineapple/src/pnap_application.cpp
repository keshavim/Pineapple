#include "pnap_application.h"
#include <iostream>

namespace Pineapple {

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
        std::cout << "Application initialized" << std::endl;
    }

    void Application::Update() {
        // Update all layers
        for (auto& layer : m_LayerStack) {
            layer->OnUpdate();
        }
    }

    void Application::Run() {
        Init();

        std::cout << "Application starting main loop" << std::endl;

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

        std::cout << "Application shutting down" << std::endl;
    }

}
