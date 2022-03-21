//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_GUI_UILAYER_H
#define BOUNCE_GUI_UILAYER_H

#include "App/Layers/ImGuiLayer.h"

namespace Bounce::Gui {

    class UILayer : public ImGuiLayer {
    public:
        void OnAttach() override;

        void OnDetach() override;

        void OnImGuiRender() override;
    };

}

#endif //BOUNCE_GUI_UILAYER_H
