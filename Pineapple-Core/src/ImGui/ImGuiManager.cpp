#include "ImGuiManager.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>

// =================== Initialization ===================
namespace pap
{


void ImGuiManager::init(GLFWwindow *window)
{
    m_Window = window;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; //doesn't work on wayland

    ImGui::StyleColorsDark();

    // Clipboard
    setupClipboard();

    // Renderer backend
    ImGui_ImplOpenGL3_Init("#version 460");

    // Timing
    m_LastTime = glfwGetTime();
}

// =================== Frame lifecycle ===================

void ImGuiManager::newFrame(float dt)
{
    ImGuiIO& io = ImGui::GetIO();

    io.DeltaTime = dt;

    // 🧭 Update display size manually
    int display_w, display_h;
    int window_w, window_h;
    glfwGetFramebufferSize(m_Window, &display_w, &display_h);
    glfwGetWindowSize(m_Window, &window_w, &window_h);

    io.DisplaySize = ImVec2((float)window_w, (float)window_h);
    io.DisplayFramebufferScale = ImVec2(
        window_w > 0 ? (float)display_w / window_w : 0.0f,
        window_h > 0 ? (float)display_h / window_h : 0.0f
    );

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow *backup = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup);
    }
}

void ImGuiManager::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

ImGuiManager::~ImGuiManager()
{
    if (ImGui::GetCurrentContext())
        shutdown();
}

// =================== Clipboard ===================

void ImGuiManager::setupClipboard()
{
    ImGuiIO &io = ImGui::GetIO();
    io.SetClipboardTextFn = setClipboardText;
    io.GetClipboardTextFn = getClipboardText;
    io.ClipboardUserData = m_Window;
}

const char *ImGuiManager::getClipboardText(void *user_data)
{
    return glfwGetClipboardString((GLFWwindow *)user_data);
}

void ImGuiManager::setClipboardText(void *user_data, const char *text)
{
    glfwSetClipboardString((GLFWwindow *)user_data, text);
}

// =================== Event Handling ===================

void ImGuiManager::onEvent(Event::Base &e)
{
    ImGuiIO &io = ImGui::GetIO();

    // Keyboard pressed
    Event::dispatch<Event::KeyPressed>(e, [&](Event::KeyPressed &ev) {
        ImGuiKey key = glfwToImGuiKey(ev.key);
        io.AddKeyEvent(key, true);
        updateModifiers(io);
    });

    // Keyboard released
    Event::dispatch<Event::KeyReleased>(e, [&](Event::KeyReleased &ev) {
        ImGuiKey key = glfwToImGuiKey(ev.key);
        io.AddKeyEvent(key, false);
        updateModifiers(io);
    });

    // Character input
    Event::dispatch<Event::CharTyped>(e, [&](Event::CharTyped &ev) { io.AddInputCharacter(ev.character); });

    // Mouse buttons
    Event::dispatch<Event::MouseButtonPressed>(e, [&](Event::MouseButtonPressed &ev) {
        io.AddMouseButtonEvent(ev.button, true);
    });
    Event::dispatch<Event::MouseButtonReleased>(e, [&](Event::MouseButtonReleased &ev) {
        io.AddMouseButtonEvent(ev.button, false);
    });

    // Mouse moved
    Event::dispatch<Event::MouseMoved>(e,
                                       [&](Event::MouseMoved &ev) { io.AddMousePosEvent((float)ev.x, (float)ev.y); });

    // Mouse scroll
    Event::dispatch<Event::MouseScrolled>(e, [&](Event::MouseScrolled &ev) {
        io.AddMouseWheelEvent(ev.xOffset, ev.yOffset);
    });

    // Window focus
    Event::dispatch<Event::WindowFocused>(e, [&](Event::WindowFocused &ev) { io.AddFocusEvent(ev.focused); });
}

// =================== Helpers ===================

ImGuiKey ImGuiManager::glfwToImGuiKey(int key)
{
    switch (key)
    {
    case GLFW_KEY_TAB:
        return ImGuiKey_Tab;
    case GLFW_KEY_LEFT:
        return ImGuiKey_LeftArrow;
    case GLFW_KEY_RIGHT:
        return ImGuiKey_RightArrow;
    case GLFW_KEY_UP:
        return ImGuiKey_UpArrow;
    case GLFW_KEY_DOWN:
        return ImGuiKey_DownArrow;
    case GLFW_KEY_PAGE_UP:
        return ImGuiKey_PageUp;
    case GLFW_KEY_PAGE_DOWN:
        return ImGuiKey_PageDown;
    case GLFW_KEY_HOME:
        return ImGuiKey_Home;
    case GLFW_KEY_END:
        return ImGuiKey_End;
    case GLFW_KEY_INSERT:
        return ImGuiKey_Insert;
    case GLFW_KEY_DELETE:
        return ImGuiKey_Delete;
    case GLFW_KEY_BACKSPACE:
        return ImGuiKey_Backspace;
    case GLFW_KEY_SPACE:
        return ImGuiKey_Space;
    case GLFW_KEY_ENTER:
        return ImGuiKey_Enter;
    case GLFW_KEY_ESCAPE:
        return ImGuiKey_Escape;
    case GLFW_KEY_A:
        return ImGuiKey_A;
    case GLFW_KEY_C:
        return ImGuiKey_C;
    case GLFW_KEY_V:
        return ImGuiKey_V;
    case GLFW_KEY_X:
        return ImGuiKey_X;
    case GLFW_KEY_Y:
        return ImGuiKey_Y;
    case GLFW_KEY_Z:
        return ImGuiKey_Z;
    default:
        return ImGuiKey_None;
    }
}

void ImGuiManager::updateModifiers(ImGuiIO &io)
{
    GLFWwindow *ctx = glfwGetCurrentContext();
    io.AddKeyEvent(ImGuiMod_Ctrl,
                   glfwGetKey(ctx, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
                       glfwGetKey(ctx, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS);
    io.AddKeyEvent(ImGuiMod_Shift,
                   glfwGetKey(ctx, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
                       glfwGetKey(ctx, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);
    io.AddKeyEvent(ImGuiMod_Alt,
                   glfwGetKey(ctx, GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
                       glfwGetKey(ctx, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS);
    io.AddKeyEvent(ImGuiMod_Super,
                   glfwGetKey(ctx, GLFW_KEY_LEFT_SUPER) == GLFW_PRESS ||
                       glfwGetKey(ctx, GLFW_KEY_RIGHT_SUPER) == GLFW_PRESS);
}
} // namespace pap
