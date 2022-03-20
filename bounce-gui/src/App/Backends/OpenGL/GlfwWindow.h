//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_GUI_GLFWWINDOW_H
#define BOUNCE_GUI_GLFWWINDOW_H

#include "App/Window.h"
#include "App/Renderer/Context.h"


#define GLFW_INCLUDE_NONE  // Avoid double GL inclusion from glad
#include "GLFW/glfw3.h"


namespace Bounce::Gui {

    static bool s_GlfwInitialized = false;

    class GlfwWindow : public Window {
    public:
        explicit GlfwWindow(const WindowProperties &properties);
        ~GlfwWindow() override;

        void OnUpdate() override;

        [[nodiscard]] inline unsigned int GetWidth() const override {
            return m_windowData.width;
        }
        [[nodiscard]] inline unsigned int GetHeight() const override {
            return m_windowData.height;
        }
        inline void SetEventCallback(EventCallbackFn callback) override {
            m_windowData.EventCallback = callback;
        }

        static void HandleGlfwError(int error, const char* description);

    private:
        GLFWwindow* m_window;
        RenderContext* m_context;

        struct WindowData {
            std::string title;
            unsigned int width, height;

            EventCallbackFn EventCallback;
        };

        WindowData m_windowData;
    };

}


#endif //BOUNCE_GUI_GLFWWINDOW_H
