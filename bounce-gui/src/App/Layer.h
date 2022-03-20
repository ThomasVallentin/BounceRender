//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_GUI_LAYER_H
#define BOUNCE_GUI_LAYER_H

#include "Event.h"

#include <memory>
#include <vector>
#include <cstdio>


namespace Bounce::Gui {

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

#endif //BOUNCE_GUI_LAYER_H
