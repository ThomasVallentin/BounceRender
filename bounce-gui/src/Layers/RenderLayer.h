//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef BOUNCE_RENDERLAYER_H
#define BOUNCE_RENDERLAYER_H


#include "App/Core/Layer.h"

#include "App/Events/ApplicationEvent.h"
#include "App/Renderer/VertexArray.h"
#include "App/Renderer/Material.h"
#include "App/Renderer/Camera.h"
#include "App/Renderer/FrameBuffer.h"


namespace Bounce::Gui {
    class RenderLayer : public Layer {
    public:
        RenderLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event &event) override;

        void OnImGuiRender() override;

    private:
        bool OnWindowResizeEvent(WindowResizeEvent &event);

        bool m_showSceneHierarchy = true;
        bool m_showPropertyView = true;

        std::shared_ptr<VertexArray> m_vertexArray;
        std::shared_ptr<VertexArray> m_floorVA;
        std::shared_ptr<Material> m_material;

        // WARNING(tvallentin): Camera used to be a simple attribute instead of
        // a shared pointer to a Camera but this caused crashes when
        // allocating / deallocating memory for strings for an unknown reason.
        // We'll deal with this when we'll start implementing the Scene/Entity system,
        // since then let's keep it that way.
        std::shared_ptr<Camera> m_camera;

        std::shared_ptr<FrameBuffer> m_viewportFrameBuffer;
        float m_viewportWidth, m_viewportHeight;
    };

}

#endif //BOUNCE_RENDERLAYER_H
