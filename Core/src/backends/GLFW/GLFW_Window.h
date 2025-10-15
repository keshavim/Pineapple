// GLFWWindow.h
#pragma once

#include "core/Window.h"
#include "renderer/RendererContext.h"


struct GLFWwindow;

namespace pap
{

class GLFWWindowBackend : public Window
{
public:
    GLFWWindowBackend(const WindowSpecifications &specs);
    ~GLFWWindowBackend() override;

    void Create() override;
    void Destroy() override;
    void Update() override;
    bool ShouldClose() const override;
    void SetVSync(bool enabled) override;

    std::pair<int, int> GetFramebufferSize() override;
    std::pair<int, int> GetWindowSize() const override;

    void *GetNativeHandle() const override
    {
        return m_Window;
    }
    WindowBackend GetWindowBackend() const override
    {
        return WindowBackend::GLFW;
    }


    const std::string &GetTitle() const override
    {
        return m_Data.Title;
    }
    int GetWidth() const override
    {
        return m_Data.Width;
    }
    int GetHeight() const override
    {
        return m_Data.Height;
    }
    bool IsVSync() const override
    {
        return m_Data.VSync;
    }

    void SetEventCallback(const EventCallbackFn &callback) override
    {
        m_Data.EventCallback = callback;
    }

private:
    struct Data
    {
        std::string Title;
        int Width;
        int Height;
        bool VSync;
        bool Resizable;
        EventCallbackFn EventCallback;
    };

    Data m_Data;
    GLFWwindow *m_Window = nullptr;
    RendererContext *m_Context = nullptr;
};

} // namespace pap
