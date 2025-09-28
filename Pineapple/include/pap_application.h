#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include "pap_layer.h"

namespace pap {

    class Application {
    public:
        Application();
        virtual ~Application();

        // Basic application lifecycle functions
        void Init();
        void Update();
        void Run();

        // Template function for pushing layer instances
        template<typename T>
        void PushLayer() {
            static_assert(std::is_base_of_v<Layer, T>, "T must be derived from Layer");
            auto layer = std::make_unique<T>();
            layer->OnAttach();
            m_LayerStack.push_back(std::move(layer));
        }

        template<typename T, typename... Args>
        void PushLayer(Args&&... args) {
            static_assert(std::is_base_of_v<Layer, T>, "T must be derived from Layer");
            auto layer = std::make_unique<T>(std::forward<Args>(args)...);
            layer->OnAttach();
            m_LayerStack.push_back(std::move(layer));
        }

        static Application& Get() { return *s_Instance; }

    private:
        std::vector<std::unique_ptr<Layer>> m_LayerStack;
        bool m_Running = true;
        static Application* s_Instance;
    };

    // To be defined by client
    std::unique_ptr<Application> CreateApplication();

}
