#pragma once
#include <string>

namespace pap {

class Layer {
public:
    Layer(const std::string& name = "Layer") : m_Name(name) {}
    virtual ~Layer() = default;

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate(float dt) {}
    virtual void onRender() {}

    const std::string& getName() const { return m_Name; }

private:
    std::string m_Name;
};


}  // namespace Pineapple
