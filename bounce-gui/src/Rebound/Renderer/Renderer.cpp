//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "Renderer.h"

#include "Rebound/Backends/OpenGL/OpenGLRenderer.h"

namespace Rebound {

    std::vector<RenderItem*> Renderer::s_renderItems;
    RenderSceneData Renderer::s_sceneData = RenderSceneData();
    RenderAPI Renderer::s_renderApi = RenderAPI::OpenGL;
    RenderHints Renderer::s_renderHints;

    void Renderer::Begin(Camera &camera) {
        s_sceneData.viewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::End() {
        // Consolidation ?
    }

    void Renderer::Submit(RenderItem *renderItem)  {
        s_renderItems.push_back(renderItem);
    }

    void Renderer::Flush() {
        switch (GetAPI()) {
            case RenderAPI::None:    break;
            case RenderAPI::OpenGL:  OpenGLRenderer::Flush(); break;
        }

        s_renderItems.clear();
    }

    void Renderer::SetRenderHints(const RenderHints &hints) {
        switch (GetAPI()) {
            case RenderAPI::None:    return;
            case RenderAPI::OpenGL:  OpenGLRenderer::SetRenderHints(hints);
        }
    }
}
