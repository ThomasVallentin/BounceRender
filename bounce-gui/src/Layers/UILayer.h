//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_UILAYER_H
#define BOUNCE_UILAYER_H

#include "App/Layers/ImGuiLayer.h"

class UILayer : public Bounce::Gui::ImGuiLayer {
public:
    void OnAttach() override;
    void OnDetach() override;

    void OnImGuiRender() override;
};


#endif //BOUNCE_UILAYER_H
