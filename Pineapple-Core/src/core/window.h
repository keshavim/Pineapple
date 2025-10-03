#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace pap
{


struct WindowSpecifications
{
    std::string Title = "Pineapple";
    int Width = 1280;
    int Height = 720;
    bool VSync = true;
    bool Resizable = true;
};

class Window
{
public:
    explicit Window(const WindowSpecifications &specs = WindowSpecifications());
    ~Window();

    void Create();
    void Destroy();

    void Update(); // Runs per-frame
    bool ShouldClose() const;
    void SetVSync(bool enabled);
    inline bool IsVSync() const
    {
        return m_Specs.VSync;
    }

    inline GLFWwindow *GetNativeWindow() const
    {
        return m_Window;
    }

    std::pair<int, int> GetFramebufferSize();

private:
private:
    WindowSpecifications m_Specs;
    GLFWwindow *m_Window = nullptr;
};

} // namespace pap
