//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef RBND_LAYER_H
#define RBND_LAYER_H

#include "Event.h"

#include <memory>
#include <vector>
#include <cstdio>


namespace Rebound {

    class Layer {
    public:
        virtual ~Layer() = default;

        virtual void OnAttach() {};
        virtual void OnUpdate() {};
        virtual void OnDetach() {};
        virtual void OnImGuiRender() {};

        virtual void OnEvent(Event &event) {};
    };

}

#endif //RBND_LAYER_H
