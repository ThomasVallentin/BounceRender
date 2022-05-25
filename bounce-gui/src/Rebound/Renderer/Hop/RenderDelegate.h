//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef HOP_RENDERER_H
#define HOP_RENDERER_H

#include "Item.h"

#include "Rebound/Renderer/RenderDelegate.h"

#include <vector>

namespace Hop {

    enum class RenderAPI {
        None = 0,
        OpenGL = 1
    };

    enum class DisplayMode {
        SmoothShaded = 0,
        HardShaded,
        Wireframe,
    };

    enum class LightingMode {
        DefaultLighting = 0,
        SceneLighting,
        FlatLighting,
    };

    struct RenderHints {
        DisplayMode displayMode;
        LightingMode lightingMode;
    };

    class RenderDelegate : public Rebound::RenderDelegate {
    public:
        RenderDelegate() : Rebound::RenderDelegate(nullptr) {}
        explicit RenderDelegate(Rebound::RenderScene *scene) : Rebound::RenderDelegate(scene) {}

        bool Render(Rebound::Camera *camera) override;

        Rebound::RenderEntity *CreateRenderEntity(const Rebound::EntityDataHandle &handle) override;

        inline static RenderAPI GetAPI()  { return s_renderApi; }

        inline static RenderHints GetRenderHints()  { return s_renderHints; }
        static void SetRenderHints(const RenderHints &hints);

    protected:
        static std::vector<DrawItem *> s_DrawItems;

        static RenderAPI s_renderApi;
        static RenderHints s_renderHints;
    };
}


#endif //HOP_RENDERER_H
