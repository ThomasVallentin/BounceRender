//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef HOP_OPENGLRENDERER_H
#define HOP_OPENGLRENDERER_H

#include "Rebound/Renderer/Hop/RenderDelegate.h"


namespace Hop {

    class OpenGLRenderer {
    public:
        static void Render(RenderDelegate *delegate, Rebound::Camera *camera);
        static void ApplyRenderHints(const RenderHints& hints);
    };

}


#endif //HOP_OPENGLRENDERER_H
