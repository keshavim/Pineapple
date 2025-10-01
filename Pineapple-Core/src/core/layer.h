#pragma once
#include <string>

namespace pap {

    class Layer {
    public:
        Layer() = default;
        virtual ~Layer() = default;

        virtual void OnUpdate(float dt);
        virtual void OnRender();
        //virtual void OnEvent(Event$ event);
    };

}  // namespace Pineapple
