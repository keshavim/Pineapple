// Window.h
#pragma once

#include "core.h"
#include "event.h"
#include <functional>
#include <string>
#include <utility>

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

enum class WindowBackend{
    None,
    GLFW,
};


class Window
{
public:
    virtual ~Window() = default;

    virtual void Create() = 0;
    virtual void Destroy() = 0;
    virtual void Update() = 0;
    virtual bool ShouldClose() const = 0;
    virtual void SetVSync(bool enabled) = 0;

    virtual std::pair<int, int> GetFramebufferSize() = 0;
    virtual std::pair<int, int> GetWindowSize() const = 0;

    virtual void *GetNativeHandle() const = 0;
    virtual WindowBackend GetWindowBackend() const = 0;

    virtual const std::string &GetTitle() const = 0;
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
    virtual bool IsVSync() const = 0;

    virtual void SetEventCallback(const EventCallbackFn &callback) = 0;

    static Window *CreatePlatformWindow(const WindowSpecifications &specs);
};


} // namespace pap
