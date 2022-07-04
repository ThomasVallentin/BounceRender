//
// Created by Thomas Vallentin on 02/07/2022.
//

#include "RenderDelegate.h"
#include "FrameBuffer.h"
#include "Mesh.h"

#include "Rebound/Renderer/RenderScene.h"
#include "Rebound/Renderer/Camera.h"
#include "Rebound/Scene/Entities/Mesh.h"

#include "BounceRender/Core/Camera.h"

namespace Rebound {

    // BncRenderSharedData

    BncRenderSharedData::BncRenderSharedData(Bounce::Scene *scene, std::thread *renderTread)
            : m_scene(scene), m_renderThread(renderTread) {}

    Bounce::Scene *BncRenderSharedData::AcquireScene() {
        if (m_renderThread->joinable())
            m_renderThread->join();

        return m_scene;
    }

    BncRenderSettings *BncRenderSharedData::GetRenderSettings() {
        return &m_renderSettings;
    }

    // BncRenderDelegate

    BncRenderDelegate::BncRenderDelegate() : RenderDelegate() {
        m_scene = new Bounce::Scene();
        m_integrator = new Bounce::Raytracer(m_scene);
        m_sharedData = new BncRenderSharedData(m_scene, &m_renderThread);
    }

    BncRenderDelegate::BncRenderDelegate(Rebound::RenderScene *scene)
        : RenderDelegate(scene) {
        m_sharedData = new BncRenderSharedData(new Bounce::Scene, &m_renderThread);
    }

    BncRenderDelegate::~BncRenderDelegate() {
        Stop();
    }

    bool BncRenderDelegate::IsRunning() {
        return m_isRunning;
    }

    bool BncRenderDelegate::Stop() {
        m_integrator->Stop();

        if (m_renderThread.joinable())
            m_renderThread.join();

        return true;
    }

    bool BncRenderDelegate::Restart() {
        m_integrator->Stop();
        Render();
        return true;
    }

    bool BncRenderDelegate::Render() {
        if (m_renderThread.joinable())
            m_renderThread.join();

        // Ensure that the embree scene is up-to-date
        m_scene->Commit();

        m_isRunning = true;

        // Starting the render thread
        m_renderThread = std::thread([&]() {
            auto framebuffer = std::dynamic_pointer_cast<BncFrameBuffer>(GetFrameBuffer());
            auto specs = framebuffer->GetSpecifications();

            m_integrator->Render(framebuffer->GetPixels().data(),
                                 specs->width,
                                 specs->height,
                                 m_sharedData->GetRenderSettings()->sampleCount,
                                 m_currentCamera);

            m_isRunning = false;
        });

        return true;
    }

    bool BncRenderDelegate::Render(Camera *camera) {
        m_currentCamera = BncCamFromCamera(camera);

        return Render();
    }

    Bounce::Camera *BncRenderDelegate::BncCamFromCamera(Camera *camera) const {
        Bounce::Vec2f resolution = {500, 500};
        Bounce::Vec2f filmGate = {21.946, 16.002};
        float focalLength = filmGate.x / tanf(glm::radians(camera->GetFov()) * 0.5f) * 0.5f;

        Bounce::Mat4f camTransform;
        camTransform.translate(Bounce::Vec3f(camera->GetPosition()));
        camTransform.rotate(Bounce::Vec3f(camera->GetEulerAngles()));

        return new Bounce::ThinLensCamera(
                camTransform,
                resolution,
                filmGate,
                focalLength);
    }

    RenderEntity *BncRenderDelegate::CreateRenderEntity(const EntityDataHandle &handle) {
        auto entity = GetRenderScene()->GetEntity(handle);

        if (entity.IsA<Mesh>()) {
            // TODO: Since we don't have a proper Material system in the scene,
            //  we pass an empty handle. The renderer will then use the delegate's default material
            //  This should be replaced by passing the mesh's assignation data instead.
            return new BncMesh(entity, 0);
        }

        return nullptr;
    }

    std::shared_ptr<Material> BncRenderDelegate::CreateMaterial(const EntityDataHandle &handle) {
        // TODO: Implement this
        return nullptr;
    }

    std::shared_ptr<FrameBuffer>
    BncRenderDelegate::CreateFrameBuffer(FrameBufferSpec *spec) const {
        return BncFrameBuffer::Create(spec);
    }

    RenderSharedData *BncRenderDelegate::GetSharedData() const {
        return m_sharedData;
    }

}
