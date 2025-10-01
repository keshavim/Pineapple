#pragma  once
#include <string>
#include <functional>


namespace pap{
// Abstract base class for ImGui windows

class ImGuiWindow {
public:
    ImGuiWindow(const std::string& title);
    ~ImGuiWindow();

    // Add UI elements
    void addText(const std::string& text);

    void addButton(const std::string& label, std::function<void()> onClick);

    void IsDemoWindow();

    // Draw the window
    void draw();

    const std::string& getTitle() const { return m_Title; }

private:
    std::string m_Title;
    std::vector<std::function<void()>> m_Elements;

    bool isDemo = false;
};

}
