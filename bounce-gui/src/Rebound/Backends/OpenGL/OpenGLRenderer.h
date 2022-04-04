//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef RBND_OPENGLRENDERER_H
#define RBND_OPENGLRENDERER_H

#include "Rebound/Renderer/Renderer.h"

namespace Rebound {

    class OpenGLRenderer : public Renderer {
    public:
        static void Flush();

        static void SetRenderHints(const RenderHints& hints);
    };

}


#endif //RBND_OPENGLRENDERER_H
