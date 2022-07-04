//
// Created by Thomas Vallentin on 02/07/2022.
//

#ifndef RBND_RENDERVIEW_H
#define RBND_RENDERVIEW_H


#include "Rebound/Core/Widget.h"

#include "Rebound/Renderer/Bounce/FrameBuffer.h"
#include "Rebound/Renderer/Bounce/RenderDelegate.h"

#include "Rebound/Renderer/Hop/FrameBuffer.h"
#include "Rebound/Renderer/Hop/VertexArray.h"
#include "Rebound/Renderer/Hop/Material.h"

namespace Rebound {

    class RenderViewWidget : public Widget {
    public:
        RenderViewWidget();

        void SetRenderDelegate(std::shared_ptr<BncRenderDelegate> renderDelegate);
        std::shared_ptr<BncRenderDelegate> GetRenderDelegate() const;
        void SetCamera(std::shared_ptr<Camera> camera);

        void PreRender() override;
        void Render() override;
        void PostRender() override;

        void Start() const;
        void Stop() const;
        void Restart() const;

        bool IsInteractive() const;

    private:
        void UpdateFromRenderBuffer();
        void UpdateFrameBuffer();

        std::shared_ptr<BncRenderDelegate> m_renderDelegate;

        std::shared_ptr<Hop::FrameBuffer> m_frameBuffer;
        std::shared_ptr<Hop::VertexArray> m_renderQuad;
        std::shared_ptr<Hop::Material> m_renderQuadMaterial;
        std::shared_ptr<Camera> m_camera;
        uint32_t m_renderTextureId;

        bool m_interactive = false;
    };

}


#endif // RBND_RENDERVIEW_H
