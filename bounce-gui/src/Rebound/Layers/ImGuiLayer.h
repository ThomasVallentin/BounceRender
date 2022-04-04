//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef RBND_IMGUILAYER_H
#define RBND_IMGUILAYER_H

#include "Rebound/Core/Layer.h"
#include "Rebound/Events/ApplicationEvent.h"
#include "Rebound/Events/MouseEvent.h"
#include "Rebound/Events/KeyEvent.h"

namespace Rebound {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer() = default;

        void OnAttach() override;

        void Begin();
        void End();
    };

}



#endif //RBND_IMGUILAYER_H
