//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef BOUNCE_GUI_OPENGLCONTEXT_H
#define BOUNCE_GUI_OPENGLCONTEXT_H

#include "App/Renderer/Context.h"


struct GLFWwindow;

namespace Bounce::Gui {

    class OpenGLContext : public RenderContext {
    public:
        explicit OpenGLContext(GLFWwindow *windowHandle)
                : RenderContext(),
                  m_windowHandle(windowHandle) {}

        void Init() override;
        void SwapBuffers() override;

    private:
        GLFWwindow *m_windowHandle;
    };

}

#endif //BOUNCE_GUI_OPENGLCONTEXT_H
