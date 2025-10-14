// GLFWWindow.h
#pragma once

#include "core/Window.h"
#include <GLFW/glfw3.h>

namespace pap
{

class GLFWWindow : public Window
{
public:
    GLFWWindow(const WindowSpecifications &specs);
    ~GLFWWindow() override;

    void Create() override;
    void Destroy() override;
    void Update() override;
    bool ShouldClose() const override;
    void SetVSync(bool enabled) override;

    std::pair<int, int> GetFramebufferSize() override;
    std::pair<int, int> GetWindowSize() const override;

    void *GetNativeHandle() const override { return m_Window; }
    WindowPlatform GetPlatform() const override {return WindowPlatform::GLFW;}


    const std::string &GetTitle() const override { return m_Data.Title; }
    int GetWidth() const override { return m_Data.Width; }
    int GetHeight() const override { return m_Data.Height; }
    bool IsVSync() const override { return m_Data.VSync; }

    void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }

private:
    struct Data
    {
        std::string Title;
        int Width;
        int Height;
        bool VSync;
        bool Resizable;
        RendererBackendType rendererbackend;
        EventCallbackFn EventCallback;
    };

    Data m_Data;
    GLFWwindow *m_Window = nullptr;
};

} // namespace pap
