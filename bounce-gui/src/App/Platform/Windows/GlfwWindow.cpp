//
// Created by Thomas Vallentin on 17/03/2022.
//

#include "GlfwWindow.h"

#include "App/Events/ApplicationEvent.h"
#include "App/Events/MouseEvent.h"
#include "App/Events/KeyEvent.h"

#include "App/Backends/OpenGL/OpenGLContext.h"

namespace Bounce::Gui {

    void GlfwWindow::HandleGlfwError(int error, const char* description)
    {
        fprintf(stderr, "Bounce::Gui Glfw ERROR %d: %s\n", error, description);
    }

    GlfwWindow::GlfwWindow(const WindowProperties &properties) {
        // Setting internal data from the given properties
        m_windowData.title = properties.title;
        m_windowData.width = properties.width;
        m_windowData.height = properties.height;

        if (!s_GlfwInitialized) {
            // Initialize Glfw
            glfwInit();
            glfwSetErrorCallback(GlfwWindow::HandleGlfwError);

            // Decide GL+GLSL versions
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            s_GlfwInitialized = true;
        }

        // Create window with graphics context
        m_window = glfwCreateWindow(properties.width,
                                  properties.height,
                                  properties.title.c_str(),
                                  nullptr,
                                  nullptr);

        m_context = new OpenGLContext(m_window);
        m_context->Init();

        glfwSetWindowUserPointer(m_window, &m_windowData);
        // Enable vsync
        glfwSwapInterval(1);

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        // Create Window Size Callback : Update internal window size data.
        glfwSetWindowSizeCallback(m_window,
                                  [](GLFWwindow *window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.width = width;
            data.height = height;
            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_window,
                                 [](GLFWwindow* window, double xpos, double ypos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float) xpos, (float) ypos);
            data.EventCallback(event);
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            WindowData& data = *(WindowData *) glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float) xoffset, (float) yoffset);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_window,
                                   [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData *) glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    MousePressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetKeyCallback(m_window,[](GLFWwindow *window,
                                                      int key,
                                                      int scancode,
                                                      int action,
                                                      int mods)
        {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(KeyCode(key), false);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event { KeyCode(key) };
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(KeyCode(key), true);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_window,[](GLFWwindow* window, uint32_t codepoint)
        {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            KeyTypedEvent event { KeyCode(codepoint) };
            data.EventCallback(event);
        });

    }

    GlfwWindow::~GlfwWindow() {
        glfwDestroyWindow(m_window);
    }

    void GlfwWindow::OnUpdate() {
        glfwPollEvents();
        m_context->SwapBuffers();
    }

    Window* Window::Create(const WindowProperties &properties) {
        return new GlfwWindow(properties);
    }
}

