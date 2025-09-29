#pragma once
#include <string>

namespace pap {

    class Layer {
    public:
        Layer(const std::string& name = "layer");
        virtual ~Layer() = default;

        virtual void OnUpdate(float dt);
        virtual void OnRender();

        //virtual void OnEvent(Event$ event);

        const std::string& GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };

}  // namespace Pineapple
