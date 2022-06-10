//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef HOP_RENDERER_H
#define HOP_RENDERER_H

#include "DrawItem.h"
#include "FrameBuffer.h"

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
    };

    struct RenderHints {
        DisplayMode displayMode;
        LightingMode lightingMode;
    };

    class RenderDelegate : public Rebound::RenderDelegate {
    public:
        RenderDelegate();
        explicit RenderDelegate(Rebound::RenderScene *scene);

        bool Render(Rebound::Camera *camera) override;

        Rebound::RenderEntity *CreateRenderEntity(const Rebound::EntityDataHandle &handle) override;
        std::shared_ptr<Rebound::Material> CreateMaterial(const Rebound::EntityDataHandle &handle) override;

        inline static RenderAPI GetAPI()  { return s_renderApi; }

        inline RenderHints GetRenderHints() { return m_renderHints; }
        inline void SetRenderHints(const RenderHints &hints) { m_renderHints = hints; }

        std::shared_ptr<Rebound::FrameBuffer>
        CreateFrameBuffer(Rebound::FrameBufferSpec *spec) const override;

    protected:
        static RenderAPI s_renderApi;

        RenderHints m_renderHints;

    private:
        void Initialize();
    };

}


#endif //HOP_RENDERER_H
