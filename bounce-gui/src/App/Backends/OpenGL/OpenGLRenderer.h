//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef BOUNCE_GUI_OPENGLRENDERER_H
#define BOUNCE_GUI_OPENGLRENDERER_H

#include "App/Renderer/Renderer.h"

namespace Bounce::Gui {

    class OpenGLRenderer : public Renderer {
    public:
        static void Flush();

        static void SetRenderHints(const RenderHints& hints);
    };

}


#endif //BOUNCE_GUI_OPENGLRENDERER_H
