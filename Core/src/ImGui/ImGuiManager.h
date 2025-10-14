#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H

#include "core/event.h" // Your event base and subclasses
#include <imgui.h>
#include <string>
#include "core/Window.h"


struct GLFWwindow;

namespace pap
{
class ImGuiManager
{
public:
    ImGuiManager() = default;
    ~ImGuiManager();

    // Called once after you create the GLFW window
    void init(Window& window);

    // Called each frame before rendering your UI
    void newFrame(float dt);

    // Called each frame after UI rendering
    void render();

    // Called once at shutdown
    void shutdown();

    // Called from your application's event handling
    void onEvent(Event::Base &e);

private:
    Window* m_Window = nullptr;
    double m_LastTime = 0.0;

    void setupClipboard();
    static const char *getClipboardText(void *user_data);
    static void setClipboardText(void *user_data, const char *text);


    ImGuiKey toImGuiKey(KeyCode key) const;
};
} // namespace pap
#endif
