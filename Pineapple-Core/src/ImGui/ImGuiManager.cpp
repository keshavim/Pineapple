#include "ImGuiManager.h"
#include "backends/imgui_impl_opengl3.h"
#include "core/keycodes.h"
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
    ImGuiIO &io = ImGui::GetIO();

    io.DeltaTime = dt;

    // 🧭 Update display size manually
    int display_w, display_h;
    int window_w, window_h;
    glfwGetFramebufferSize(m_Window, &display_w, &display_h);
    glfwGetWindowSize(m_Window, &window_w, &window_h);

    io.DisplaySize = ImVec2((float)window_w, (float)window_h);
    io.DisplayFramebufferScale =
        ImVec2(window_w > 0 ? (float)display_w / window_w : 0.0f, window_h > 0 ? (float)display_h / window_h : 0.0f);

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

    // Key pressed
PAP_EVENT_DISPATCH(Event::KeyPressed, e,
    ImGuiKey key = toImGuiKey(e.key);
    if (key != ImGuiKey_None) io.AddKeyEvent(key, true);

    switch (e.key)
    {
        case KeyCode::LeftControl: case KeyCode::RightControl: io.AddKeyEvent(ImGuiMod_Ctrl, true); break;
        case KeyCode::LeftShift:   case KeyCode::RightShift:   io.AddKeyEvent(ImGuiMod_Shift, true); break;
        case KeyCode::LeftAlt:     case KeyCode::RightAlt:     io.AddKeyEvent(ImGuiMod_Alt, true); break;
        case KeyCode::LeftSuper:   case KeyCode::RightSuper:   io.AddKeyEvent(ImGuiMod_Super, true); break;
        default: break;
    }
);

// Key released
PAP_EVENT_DISPATCH(Event::KeyReleased, e,
    ImGuiKey key = toImGuiKey(e.key);
    if (key != ImGuiKey_None) io.AddKeyEvent(key, false);

    switch (e.key)
    {
        case KeyCode::LeftControl: case KeyCode::RightControl: io.AddKeyEvent(ImGuiMod_Ctrl, false); break;
        case KeyCode::LeftShift:   case KeyCode::RightShift:   io.AddKeyEvent(ImGuiMod_Shift, false); break;
        case KeyCode::LeftAlt:     case KeyCode::RightAlt:     io.AddKeyEvent(ImGuiMod_Alt, false); break;
        case KeyCode::LeftSuper:   case KeyCode::RightSuper:   io.AddKeyEvent(ImGuiMod_Super, false); break;
        default: break;
    }
);

// Char input
PAP_EVENT_DISPATCH(Event::CharTyped, e,
    io.AddInputCharacter(e.character);
);

// Mouse buttons
PAP_EVENT_DISPATCH(Event::MouseButtonPressed, e,
    io.AddMouseButtonEvent((int)e.button, true);
);
PAP_EVENT_DISPATCH(Event::MouseButtonReleased, e,
    io.AddMouseButtonEvent((int)e.button, false);
);

// Mouse moved
PAP_EVENT_DISPATCH(Event::MouseMoved, e,
    io.AddMousePosEvent((float)e.x, (float)e.y);
);

// Mouse scroll
PAP_EVENT_DISPATCH(Event::MouseScrolled, e,
    io.AddMouseWheelEvent(e.xOffset, e.yOffset);
);

// Window focus
PAP_EVENT_DISPATCH(Event::WindowFocused, e,
    io.AddFocusEvent(e.focused);
);

}


ImGuiKey ImGuiManager::toImGuiKey(KeyCode key) const
{
    switch (key)
    {
    // Letters
    case KeyCode::A:
        return ImGuiKey_A;
    case KeyCode::B:
        return ImGuiKey_B;
    case KeyCode::C:
        return ImGuiKey_C;
    case KeyCode::D:
        return ImGuiKey_D;
    case KeyCode::E:
        return ImGuiKey_E;
    case KeyCode::F:
        return ImGuiKey_F;
    case KeyCode::G:
        return ImGuiKey_G;
    case KeyCode::H:
        return ImGuiKey_H;
    case KeyCode::I:
        return ImGuiKey_I;
    case KeyCode::J:
        return ImGuiKey_J;
    case KeyCode::K:
        return ImGuiKey_K;
    case KeyCode::L:
        return ImGuiKey_L;
    case KeyCode::M:
        return ImGuiKey_M;
    case KeyCode::N:
        return ImGuiKey_N;
    case KeyCode::O:
        return ImGuiKey_O;
    case KeyCode::P:
        return ImGuiKey_P;
    case KeyCode::Q:
        return ImGuiKey_Q;
    case KeyCode::R:
        return ImGuiKey_R;
    case KeyCode::S:
        return ImGuiKey_S;
    case KeyCode::T:
        return ImGuiKey_T;
    case KeyCode::U:
        return ImGuiKey_U;
    case KeyCode::V:
        return ImGuiKey_V;
    case KeyCode::W:
        return ImGuiKey_W;
    case KeyCode::X:
        return ImGuiKey_X;
    case KeyCode::Y:
        return ImGuiKey_Y;
    case KeyCode::Z:
        return ImGuiKey_Z;

    // Numbers
    case KeyCode::Num0:
        return ImGuiKey_0;
    case KeyCode::Num1:
        return ImGuiKey_1;
    case KeyCode::Num2:
        return ImGuiKey_2;
    case KeyCode::Num3:
        return ImGuiKey_3;
    case KeyCode::Num4:
        return ImGuiKey_4;
    case KeyCode::Num5:
        return ImGuiKey_5;
    case KeyCode::Num6:
        return ImGuiKey_6;
    case KeyCode::Num7:
        return ImGuiKey_7;
    case KeyCode::Num8:
        return ImGuiKey_8;
    case KeyCode::Num9:
        return ImGuiKey_9;

    // Function keys
    case KeyCode::F1:
        return ImGuiKey_F1;
    case KeyCode::F2:
        return ImGuiKey_F2;
    case KeyCode::F3:
        return ImGuiKey_F3;
    case KeyCode::F4:
        return ImGuiKey_F4;
    case KeyCode::F5:
        return ImGuiKey_F5;
    case KeyCode::F6:
        return ImGuiKey_F6;
    case KeyCode::F7:
        return ImGuiKey_F7;
    case KeyCode::F8:
        return ImGuiKey_F8;
    case KeyCode::F9:
        return ImGuiKey_F9;
    case KeyCode::F10:
        return ImGuiKey_F10;
    case KeyCode::F11:
        return ImGuiKey_F11;
    case KeyCode::F12:
        return ImGuiKey_F12;

    // Navigation / Editing
    case KeyCode::Escape:
        return ImGuiKey_Escape;
    case KeyCode::Enter:
        return ImGuiKey_Enter;
    case KeyCode::Tab:
        return ImGuiKey_Tab;
    case KeyCode::Backspace:
        return ImGuiKey_Backspace;
    case KeyCode::Insert:
        return ImGuiKey_Insert;
    case KeyCode::Delete:
        return ImGuiKey_Delete;
    case KeyCode::Right:
        return ImGuiKey_RightArrow;
    case KeyCode::Left:
        return ImGuiKey_LeftArrow;
    case KeyCode::Down:
        return ImGuiKey_DownArrow;
    case KeyCode::Up:
        return ImGuiKey_UpArrow;
    case KeyCode::PageUp:
        return ImGuiKey_PageUp;
    case KeyCode::PageDown:
        return ImGuiKey_PageDown;
    case KeyCode::Home:
        return ImGuiKey_Home;
    case KeyCode::End:
        return ImGuiKey_End;
    case KeyCode::CapsLock:
        return ImGuiKey_CapsLock;
    case KeyCode::ScrollLock:
        return ImGuiKey_ScrollLock;
    case KeyCode::NumLock:
        return ImGuiKey_NumLock;
    case KeyCode::PrintScreen:
        return ImGuiKey_PrintScreen;
    case KeyCode::Pause:
        return ImGuiKey_Pause;

    // Modifiers
    case KeyCode::LeftShift:
        return ImGuiKey_LeftShift;
    case KeyCode::RightShift:
        return ImGuiKey_RightShift;
    case KeyCode::LeftControl:
        return ImGuiKey_LeftCtrl;
    case KeyCode::RightControl:
        return ImGuiKey_RightCtrl;
    case KeyCode::LeftAlt:
        return ImGuiKey_LeftAlt;
    case KeyCode::RightAlt:
        return ImGuiKey_RightAlt;
    case KeyCode::LeftSuper:
        return ImGuiKey_LeftSuper;
    case KeyCode::RightSuper:
        return ImGuiKey_RightSuper;
    case KeyCode::Menu:
        return ImGuiKey_Menu;

    case KeyCode::Space:
        return ImGuiKey_Space;

    default:
        return ImGuiKey_None; // everything else
    }
}


} // namespace pap
