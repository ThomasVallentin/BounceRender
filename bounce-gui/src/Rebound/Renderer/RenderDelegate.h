//
// Created by Thomas Vallentin on 26/04/2022.
//

#ifndef RBND_RENDERDELEGATE_H
#define RBND_RENDERDELEGATE_H

#include "Rebound/Scene/Entity.h"

#include <vector>
#include <map>


namespace Rebound {

    class RenderScene;
    class RenderEntity;
    class Camera;
    class Material;
    class FrameBuffer;
    struct FrameBufferSpec;

    class RenderSharedData {
    public:
        RenderSharedData() = default;
        virtual ~RenderSharedData() = default;
    };

    class RenderDelegate {
    public:
        RenderDelegate() : m_scene(nullptr), m_defaultMaterial(nullptr) {}
        explicit RenderDelegate(RenderScene *scene) : m_scene(scene) {}
        virtual ~RenderDelegate() = default;

        virtual bool Render(Camera *camera) = 0;

        virtual bool IsRunning();
        virtual bool Stop();
        virtual bool Restart();

        virtual bool Pause();
        virtual bool Resume();

        inline void SetRenderScene(RenderScene *scene) { m_scene = scene; }
        inline RenderScene* GetRenderScene() const { return m_scene; }

        virtual RenderEntity *CreateRenderEntity(const EntityDataHandle& handle) = 0;
        virtual std::shared_ptr<Material> CreateMaterial(const EntityDataHandle& handle) = 0;

        inline std::shared_ptr<Material> GetDefaultMaterial() const { return m_defaultMaterial; }
        void SetDefaultMaterial(std::shared_ptr<Material> material);

        virtual std::shared_ptr<FrameBuffer> CreateFrameBuffer(FrameBufferSpec *spec) const = 0;
        inline std::shared_ptr<FrameBuffer> GetFrameBuffer() const { return m_frameBuffer; }
        void SetFrameBuffer(std::shared_ptr<FrameBuffer>frameBuffer);

        virtual RenderSharedData *GetSharedData() const;

    private:
        RenderScene *m_scene;

        std::shared_ptr<Material> m_defaultMaterial;

        std::shared_ptr<FrameBuffer> m_frameBuffer;
    };

}

#endif //RBND_RENDERDELEGATE_H
