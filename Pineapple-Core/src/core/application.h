#pragma once

#include <memory>
#include <vector>

#include <GLFW/glfw3.h>
#include "layer.h"
#include "window.h"
#include "odbc_manager.h"


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


        std::shared_ptr<Window> getWindow() const{
            return m_Window;
        }

        std::shared_ptr<ODBCManager> getDBCManager() const{
            return m_DBCManager;
        }


    private:
        void Update();

        AppSpecifications m_Specifications;
        std::shared_ptr<Window> m_Window;

        std::vector<std::unique_ptr<Layer>> m_LayerStack;
        bool m_Running = false;
        static Application* s_Instance;

        std::shared_ptr<ODBCManager> m_DBCManager;

    };

    struct Student {
    int id;
    std::string first;
    std::string last;
    std::string subject;
    };

    // Cached students list
    static std::vector<Student> cached_students;
    static bool students_loaded = false;

    // To be defined by client
    std::unique_ptr<Application> CreateApplication();

}
