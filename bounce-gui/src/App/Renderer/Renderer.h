//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef BOUNCE_GUI_RENDERER_H
#define BOUNCE_GUI_RENDERER_H

#include "RenderItem.h"

#include <vector>


namespace Bounce::Gui {

    enum class RenderAPI {
        None = 0,
        OpenGL = 1
    };

    struct Scene {
        // TODO(tvallentin): Add camera, lights, environment?
        std::string name;
    };

    class Renderer {
    public:
        static void BeginScene(Scene *scene);
        static void EndScene();
        static void Submit(RenderItem *renderItem);
        static void Flush();

        inline static RenderAPI GetAPI()  { return s_renderApi; }

    protected:
        static std::vector<RenderItem *> s_renderItems;
        static Scene *s_scene;

        static RenderAPI s_renderApi;
    };
}


#endif //BOUNCE_GUI_RENDERER_H
