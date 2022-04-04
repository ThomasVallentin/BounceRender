//
// Created by Thomas Vallentin on 21/03/2022.
//

#ifndef RBND_INPUTS_H
#define RBND_INPUTS_H

#include "KeyCodes.h"
#include "MouseButtons.h"

#include <glm/vec2.hpp>

namespace Rebound {

    class Input {
    public:

        static bool IsKeyPressed(const KeyCode &key);
        static bool IsMouseButtonPressed(const MouseButton &button);
        static glm::vec2 GetMousePosition();

    };

}

#endif //RBND_INPUTS_H
