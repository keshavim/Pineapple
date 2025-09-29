#pragma once

#include <memory>
#include <vector>

#include <GLFW/glfw3.h>
#include "pap_layer.h"
#include "pap_window.h"


namespace pap {
    struct AppSpecifications{
        std::string name = "Pineapple";
        WindowSpecifications winSpec;
    };

    class Application {
    public:
        Application(const AppSpecifications& spec = AppSpecifications());
        virtual ~Application();

        void Run();
        void Stop();


        // Template function for pushing layer instances
        template<typename TLayer>
		requires(std::is_base_of_v<Layer, TLayer>)
		void PushLayer()
		{
			m_LayerStack.push_back(std::make_unique<TLayer>());
		}

        static Application& Get();
        static float GetTime();


    private:
        void Update();

        AppSpecifications m_Specifications;
        std::unique_ptr<Window> m_Window;

        std::vector<std::unique_ptr<Layer>> m_LayerStack;
        bool m_Running = false;
        static Application* s_Instance;
    };

    // To be defined by client
    std::unique_ptr<Application> CreateApplication();

}
