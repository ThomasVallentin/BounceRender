//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef HOP_OPENGLRENDERER_H
#define HOP_OPENGLRENDERER_H

#include "Rebound/Renderer/Hop/RenderDelegate.h"

namespace Hop {

    class OpenGLRenderer {
    public:
        static void Render(RenderIndex *index, Rebound::Camera *camera);

        static void SetRenderHints(const RenderHints& hints);
    };

}


#endif //HOP_OPENGLRENDERER_H
