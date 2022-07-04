//
// Created by Thomas Vallentin on 02/07/2022.
//

#ifndef BOUNCE_RENDERDELEGATE_H
#define BOUNCE_RENDERDELEGATE_H

#include "Rebound/Renderer/RenderDelegate.h"

#include "BounceRender/Core/Raytracer.h"
#include "BounceRender/Core/Scene.h"

#include <thread>


namespace Rebound {

    struct BncRenderSettings {
        uint32_t sampleCount = 100;
    };

    class BncRenderSharedData : public RenderSharedData {
    public:
        BncRenderSharedData(Bounce::Scene* scene,
                            std::thread *renderTread);

        Bounce::Scene* AcquireScene();
        BncRenderSettings* GetRenderSettings();

    private:
        Bounce::Scene *m_scene;
        std::thread *m_renderThread;

        BncRenderSettings m_renderSettings;
    };

    class BncRenderDelegate : public RenderDelegate {
    public:
        BncRenderDelegate();
        explicit BncRenderDelegate(Rebound::RenderScene *scene);
        ~BncRenderDelegate() override;

        bool Render(Camera *camera) override;
        bool IsRunning() override;
        bool Stop() override;
        bool Restart() override;

        RenderEntity *CreateRenderEntity(const EntityDataHandle &handle) override;
        std::shared_ptr<Material> CreateMaterial(const EntityDataHandle &handle) override;
        std::shared_ptr<FrameBuffer> CreateFrameBuffer(FrameBufferSpec *spec) const override;

        RenderSharedData *GetSharedData() const override;

    private:
        bool Render();
        Bounce::Camera* BncCamFromCamera(Camera* camera) const;
        std::thread m_renderThread;

        Bounce::Raytracer *m_integrator;
        Bounce::Scene *m_scene;
        Bounce::Camera *m_currentCamera;

        BncRenderSharedData* m_sharedData;

        bool m_isRunning = false;
    };

}

#endif //BOUNCE_RENDERDELEGATE_H
