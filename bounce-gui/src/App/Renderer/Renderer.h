//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef BOUNCE_GUI_RENDERER_H
#define BOUNCE_GUI_RENDERER_H

#include "RenderItem.h"
#include "Camera.h"

#include <vector>


namespace Bounce::Gui {

    enum class RenderAPI {
        None = 0,
        OpenGL = 1
    };

    struct SceneData {
        glm::mat4 viewProjectionMatrix;
        // TODO(tvallentin): Add lights, environment
    };

    class Renderer {
    public:
        static void BeginScene(Camera &camera);
        static void EndScene();
        static void Submit(RenderItem *renderItem);
        // TODO(tvallentin): Replace this function by a RenderAPI implementation that calls render commands
        static void Flush();

        inline static RenderAPI GetAPI()  { return s_renderApi; }

    protected:
        static std::vector<RenderItem *> s_renderItems;
        static SceneData s_sceneData;

        static RenderAPI s_renderApi;
    };
}


#endif //BOUNCE_GUI_RENDERER_H
