//
// Created by Thomas Vallentin on 21/03/2022.
//

#include "Rebound/Core/Inputs.h"
#include "Rebound/Core/Application.h"

#include <GLFW/glfw3.h>


namespace Rebound {

    bool Input::IsKeyPressed(const KeyCode &key) {
        auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, (int) key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(const MouseButton &button){
        auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, (int) button);
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePosition(){
        auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return { (float)x, (float)y };
    }



}