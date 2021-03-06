//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef RBND_MAINLAYER_H
#define RBND_MAINLAYER_H


#include "Rebound/Core/Layer.h"

#include "Rebound/Widgets/SceneHierarchy.h"
#include "Rebound/Widgets/AttributeView.h"
#include "Rebound/Widgets/RenderView.h"

#include "Rebound/Events/ApplicationEvent.h"

#include "Rebound/Scene/Scene.h"

#include "Rebound/Renderer/Camera.h"
#include "Rebound/Renderer/RenderDelegate.h"
#include "Rebound/Renderer/Hop/RenderDelegate.h"


namespace Rebound {

    class CameraObserver;

    class MainLayer : public Layer {
    public:
        MainLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event &event) override;

        void OnImGuiRender() override;

    private:
        bool OnWindowResizeEvent(WindowResizeEvent &event);

        // Commands
        void NewScene();
        void OpenScene(const std::string& name);

        SceneHierarchyWidget m_sceneHierarchyWid;
        AttributeViewWidget m_attributeViewWid;
        RenderViewWidget m_renderView;

        // WARNING(tvallentin): Camera used to be a simple attribute instead of
        // a shared pointer to a Camera but this caused crashes when
        // allocating / deallocating memory for strings for an unknown reason.
        // We'll deal with this when we'll start implementing the Scene/Entity system,
        // since then let's keep it that way.
        std::shared_ptr<Camera> m_camera;
        CameraObserver *m_camObserver;

        float m_viewportWidth, m_viewportHeight;

        std::shared_ptr<Scene> m_scene;
        std::shared_ptr<Hop::RenderDelegate> m_vpRenderDelegate;
    };

}

#endif //RBND_MAINLAYER_H
