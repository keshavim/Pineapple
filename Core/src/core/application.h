#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <vector>

#include "ImGui/ImGuiManager.h"
#include "core/layer_manager.h"
#include "dbc/Manager.h"
#include "layer.h"
#include "window.h"
#include <GLFW/glfw3.h>

namespace pap
{

struct AppSpecifications
{
    std::string name = "Pineapple";
    WindowSpecifications winSpec;
};

class Application
{
public:
    Application() = delete; // no instances allowed

    static void Init(const AppSpecifications &spec = AppSpecifications());
    static void Shutdown();

    static void Run();
    static void Stop();
    static void OnEvent(Event::Base &e);

    static std::shared_ptr<Window> GetWindow() { return s_Window; }
    static std::pair<int, int> GetFramebufferSize();

    static db::Manager &GetDBManager() { return s_DBManager; }
    static LayerManager &GetLayerManager() { return s_LayerManager; }

    static float GetTime();

    // Layer utility functions
    template <LayerType T, typename... Args>
    static size_t PushLayer(Args &&...args)
    {
        return s_LayerManager.pushLayer(std::make_unique<T>(std::forward<Args>(args)...));
    }

    template <LayerType T, typename... Args>
    static size_t PushOverlay(Args &&...args)
    {
        return s_LayerManager.pushOverlay(std::make_unique<T>(std::forward<Args>(args)...));
    }

    static inline LayerState GetLayerState(size_t index)
    {
        return s_LayerManager.getState(index);
    }

    static inline void SetLayerState(size_t index, LayerState state)
    {
        s_LayerManager.setState(index, state);
    }

private:
    static inline AppSpecifications s_Specifications{};
    static inline std::shared_ptr<Window> s_Window = nullptr;
    static inline LayerManager s_LayerManager{};
    static inline ImGuiManager s_ImGuiManager{};
    static inline db::Manager s_DBManager{};
    static inline bool s_Running = false;
};

// To be defined by client
void CreateApplication();

} // namespace pap

#endif // APPLICATION_H
