//
// Created by Thomas Vallentin on 02/07/2022.
//

#ifndef BOUNCE_MESH_H
#define BOUNCE_MESH_H

#include "Rebound/Renderer/Mesh.h"

#include "embree3/rtcore_geometry.h"


namespace Rebound {

    class BncMesh : public RenderMesh {
    public:
        BncMesh(const Rebound::Entity& entity, const Rebound::MaterialHandle& handle);

        void Sync(const EntityInvalidation &invalidation,
                  RenderSharedData* sharedData) override;

    private:
        RTCScene m_rtcScene;

        uint32_t m_rtcId;
        RTCGeometry m_geometry = nullptr;

        std::vector<uint32_t> m_instanceIds;
        std::vector<RTCGeometry> m_instanceGeometries;
    };


}

#endif //BOUNCE_MESH_H
