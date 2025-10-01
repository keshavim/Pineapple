#pragma once
#include <string>

namespace pap {

    class Layer {
    public:

        virtual ~Layer() = default;
        virtual void OnUpdate(float dt) = 0;
        virtual void OnRender() = 0;
        //virtual void OnEvent(Event event);
    };

}  // namespace Pineapple
