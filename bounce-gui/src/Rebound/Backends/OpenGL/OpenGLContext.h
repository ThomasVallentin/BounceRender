//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef RBND_OPENGLCONTEXT_H
#define RBND_OPENGLCONTEXT_H

#include "Rebound/Renderer/Context.h"


struct GLFWwindow;

namespace Rebound {

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

#endif //RBND_OPENGLCONTEXT_H
