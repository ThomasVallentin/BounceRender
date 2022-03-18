//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_IMGUILAYER_H
#define BOUNCE_IMGUILAYER_H

#include "App/Layer.h"
#include "App/Events/ApplicationEvent.h"
#include "App/Events/MouseEvent.h"
#include "App/Events/KeyEvent.h"

namespace Bounce::Gui {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer() = default;

        void OnAttach() override;

        void Begin();
        void End();
    };

}



#endif //BOUNCE_IMGUILAYER_H
