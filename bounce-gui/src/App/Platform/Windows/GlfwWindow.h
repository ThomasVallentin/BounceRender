//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_GUI_GLFWWINDOW_H
#define BOUNCE_GUI_GLFWWINDOW_H

#include "App/Core/Window.h"
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

        inline uint32_t GetWidth() const override { return m_windowData.width; }
        inline uint32_t GetHeight() const override { return m_windowData.height; }
        inline void SetEventCallback(EventCallbackFn callback) override {
            m_windowData.EventCallback = callback;
        }

        inline void *GetNativeWindow() const override { return m_window; }

    private:
        static void HandleGlfwError(int error, const char* description);

        GLFWwindow* m_window;
        RenderContext* m_context;

        struct WindowData {
            std::string title;
            uint32_t width, height;

            EventCallbackFn EventCallback;
        };

        WindowData m_windowData;
    };

}


#endif //BOUNCE_GUI_GLFWWINDOW_H
