//
// Created by Thomas Vallentin on 02/07/2022.
//

#include "Mesh.h"
#include "RenderDelegate.h"

#include "Rebound/Scene/Entities/Mesh.h"

namespace Rebound {

    BncMesh::BncMesh(const Entity &entity, const MaterialHandle &handle)
            : Rebound::RenderMesh(entity, handle) {
    }

    void BncMesh::Sync(const EntityInvalidation &invalidation,
                       RenderSharedData* sharedData) {
        // TODO: Extremely simple implementation, we flush and recreate the draw items each time
        //  an invalidation happens
        m_drawItems.clear();

        if (invalidation.type & EntityInvalidationType::Deleted) {
            // TODO: Remove the mesh from the rtcScene
            return;
        }

        RTCScene rtcRenderScene = dynamic_cast<BncRenderSharedData*>(sharedData)->AcquireScene()->rtcScene;

        if (invalidation.type & EntityInvalidationType::Added) {
            m_rtcScene = rtcNewScene(Bounce::GetGlobalDevice());

            // Creating a new instance geometry that will reference the mesh scene
            if (m_instanceIds.empty()) {
                RTCGeometry instance = rtcNewGeometry(Bounce::GetGlobalDevice(),
                                                      RTC_GEOMETRY_TYPE_INSTANCE);
                rtcSetGeometryInstancedScene(instance, m_rtcScene);
                rtcSetGeometryTimeStepCount(instance, 1);

                rtcCommitGeometry(instance);

                // Adding the instance to the render delegate's rtcScene & storing its data
                m_instanceIds.push_back(rtcAttachGeometry(rtcRenderScene, instance));
                m_instanceGeometries.push_back(instance);
            }
        }

        if (invalidation.type & EntityInvalidationType::Added ||
            invalidation.type & EntityInvalidationType::TopologyChanged ||
            invalidation.type & EntityInvalidationType::CompleteInvalidation) {

            if (!m_geometry) {
                m_geometry = rtcNewGeometry(Bounce::GetGlobalDevice(),
                                            RTC_GEOMETRY_TYPE_TRIANGLE);
                m_rtcId = rtcAttachGeometry(m_rtcScene, m_geometry);
            }

            std::vector<glm::vec3> positions;
            GetPositions(positions);
            std::vector<uint32_t> indices;
            GetIndices(indices);

            auto *rtcVertices = (float *) rtcSetNewGeometryBuffer(m_geometry,
                                                                  RTC_BUFFER_TYPE_VERTEX,
                                                                  0,
                                                                  RTC_FORMAT_FLOAT3,
                                                                  3 * sizeof(float),
                                                                  positions.size());
            auto *rtcIndices = (unsigned *) rtcSetNewGeometryBuffer(m_geometry,
                                                                    RTC_BUFFER_TYPE_INDEX,
                                                                    0,
                                                                    RTC_FORMAT_UINT3,
                                                                    3 * sizeof(unsigned),
                                                                    indices.size() / 3);

            if (rtcVertices && rtcIndices) {
                for (size_t i = 0; i < positions.size(); i++) {
                    rtcVertices[i * 3] = positions[i].x;
                    rtcVertices[i * 3 + 1] = positions[i].y;
                    rtcVertices[i * 3 + 2] = positions[i].z;
                }

                for (size_t i = 0; i < indices.size(); i++) {
                    rtcIndices[i] = indices[i];
                }
            }
            rtcCommitGeometry(m_geometry);
            rtcCommitScene(m_rtcScene);
        }

        if (invalidation.type & EntityInvalidationType::Added ||
            invalidation.type & EntityInvalidationType::TransformChanged) {
            // Send transform to the instance
            glm::mat4 transform = m_entity.As<Mesh>().ComputeLocalToWorldMatrix();
            rtcSetGeometryTransform(m_instanceGeometries[0], 0, RTC_FORMAT_FLOAT4X4_COLUMN_MAJOR,
                                    &transform[0]);
            rtcCommitGeometry(m_instanceGeometries[0]);
        }
    }

}
