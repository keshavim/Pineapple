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
    Application(const AppSpecifications &spec = AppSpecifications());
    virtual ~Application();

    void Run();
    void Stop();

    void OnEvent(Event::Base &e);

    static Application &Get();
    static float GetTime();


    std::shared_ptr<Window> getWindow() const
    {
        return m_Window;
    }

    std::pair<int, int> GetFramebufferSize() const
    {
        return m_Window->GetFramebufferSize();
    }

    db::Manager &getDBManager()
    {
        return dbManager;
    }


    template <LayerType T, typename... Args>
    static void pushLayer(Args &&...args)
    {

        Application::Get().layerManager.pushLayer(std::make_unique<T>(std::forward<Args>(args)...));
    }

    // --- Push overlay at the end ---
    template <LayerType T, typename... Args>
    static void pushOverlay(Args &&...args)
    {
        Application::Get().layerManager.pushLayer(std::make_unique<T>(std::forward<Args>(args)...));


    }


private:
    AppSpecifications m_Specifications;
    std::shared_ptr<Window> m_Window;
    LayerManager layerManager;
    ImGuiManager imguiManager;
    db::Manager dbManager;

    bool m_Running = false;
    static Application *s_Instance;
};

// To be defined by client
void InitApplication();

} // namespace pap

#endif // APPLICATION_H
