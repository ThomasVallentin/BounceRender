//
// Created by Thomas Vallentin on 21/03/2022.
//

#ifndef BOUNCE_INPUTS_H
#define BOUNCE_INPUTS_H

#include "KeyCodes.h"
#include "MouseButtons.h"

#include <glm/vec2.hpp>

namespace Bounce::Gui {

    class Input {
    public:

        static bool IsKeyPressed(const KeyCode &key);
        static bool IsMouseButtonPressed(const MouseButton &button);
        static glm::vec2 GetMousePosition();

    };

}

#endif //BOUNCE_INPUTS_H
