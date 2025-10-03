#pragma once

#include <memory>
#include <vector>

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


private:
    void Update();

    AppSpecifications m_Specifications;
    std::shared_ptr<Window> m_Window;

    bool m_Running = false;
    static Application *s_Instance;
};

// To be defined by client
void InitApplication();

} // namespace pap
