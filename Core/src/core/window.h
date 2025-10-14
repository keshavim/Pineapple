#pragma once

#include "core.h"
#include "event.h"
#include <functional>
#include <string>


#include "renderer/Renderer.h"


namespace pap
{
using EventCallbackFn = std::function<void(Event::Base &)>;


struct WindowSpecifications
{
    std::string Title = "Pineapple";
    int Width = 1280;
    int Height = 720;
    bool VSync = true;
    bool Resizable = true;
    RendererBackendType rendererbackend = RendererBackendType::OpenGL;

};

class Window
{
public:
    Window(const WindowSpecifications &specs);
    ~Window();

    void Create();
    void Destroy();

    void Update(); // Runs per-frame
    bool ShouldClose() const;
    void SetVSync(bool enabled);
    inline bool IsVSync() const
    {
        return m_Data.VSync;
    }

    inline GLFWwindow *GetNativeWindow() const
    {
        return m_Window;
    }
    std::pair<int, int> GetFramebufferSize();
    std::pair<int, int> GetWindowSize() const;

    // -------------------------
    // Event Callback
    // -------------------------
    void SetEventCallback(const EventCallbackFn &callback)
    {
        m_Data.EventCallback = callback;
    }

    // -------------------------
    // Getters for data
    // -------------------------
    inline const std::string &GetTitle() const
    {
        return m_Data.Title;
    }
    inline int GetWidth() const
    {
        return m_Data.Width;
    }
    inline int GetHeight() const
    {
        return m_Data.Height;
    }

private:
    // -------------------------
    // Runtime Data (modifiable by events)
    // -------------------------
    struct Data
    {
        std::string Title = "Pineapple";
        int Width = 1280;
        int Height = 720;
        bool VSync = true;
        bool Resizable = true;
        RendererBackendType rendererbackend = RendererBackendType::OpenGL;


        EventCallbackFn EventCallback;
    } m_Data;

    GLFWwindow *m_Window = nullptr;
};
} // namespace pap
