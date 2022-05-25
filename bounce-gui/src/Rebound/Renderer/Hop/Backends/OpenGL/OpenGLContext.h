//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef HOP_OPENGLCONTEXT_H
#define HOP_OPENGLCONTEXT_H

#include "Rebound/Renderer/Hop/Context.h"


struct GLFWwindow;

namespace Hop {

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

#endif //HOP_OPENGLCONTEXT_H
