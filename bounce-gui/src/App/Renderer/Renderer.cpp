//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "Renderer.h"
#include "App/Backends/OpenGL/OpenGLRenderer.h"

namespace Bounce::Gui {

    RenderAPI Renderer::s_renderApi = RenderAPI::OpenGL;
    std::vector<RenderItem*> Renderer::s_renderItems;
    Scene *Renderer::s_scene = nullptr;

    void Renderer::BeginScene(Scene *scene) {
        s_scene = scene;
    }

    void Renderer::EndScene() {
        s_scene = nullptr;
    }

    void Renderer::Submit(RenderItem *renderItem)  {
        s_renderItems.push_back(renderItem);
    }

    void Renderer::Flush() {
        switch (GetAPI()) {
            case RenderAPI::None:    break;
            case RenderAPI::OpenGL:  return OpenGLRenderer::Flush();
        }
    }
}
