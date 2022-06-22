//
// Created by tvallentin on 08/03/2022.
//

#include "Scene.h"
#include "Alembic/AbcGeom/All.h"
#include "Alembic/AbcCoreFactory/All.h"
#include "Logging.h"

namespace Bounce {

    bool Scene::LoadTestGeometry() {
        /*
         * Create a triangle mesh geometry, and initialize a single triangle.
         * You can look up geometry types in the API documentation to
         * find out which type expects which buffers.
         *
         * We create buffers directly on the device, but you can also use
         * shared buffers. For shared buffers, special care must be taken
         * to ensure proper alignment and padding. This is described in
         * more detail in the API documentation.
         */
        RTCGeometry geom = rtcNewGeometry(Bounce::GetGlobalDevice(),
                                          RTC_GEOMETRY_TYPE_TRIANGLE);
        auto *vertices = (float *) rtcSetNewGeometryBuffer(geom,
                                                           RTC_BUFFER_TYPE_VERTEX,
                                                           0,
                                                           RTC_FORMAT_FLOAT3,
                                                           3 * sizeof(float),
                                                           3);

        auto *indices = (unsigned *) rtcSetNewGeometryBuffer(geom,
                                                             RTC_BUFFER_TYPE_INDEX,
                                                             0,
                                                             RTC_FORMAT_UINT3,
                                                             3 * sizeof(unsigned),
                                                             1);

        if (vertices && indices) {
            vertices[0] = 0.f;
            vertices[1] = 0.f;
            vertices[2] = 5.f;
            vertices[3] = 1.f;
            vertices[4] = 0.f;
            vertices[5] = 5.f;
            vertices[6] = 0.f;
            vertices[7] = 1.f;
            vertices[8] = 5.f;

            indices[0] = 0;
            indices[1] = 1;
            indices[2] = 2;
        }

        /*
         * You must commit geometry objects when you are done setting them up,
         * or you will not get any intersections.
         */
        rtcCommitGeometry(geom);

        /*
         * In rtcAttachGeometry(...), the scene takes ownership of the geom
         * by increasing its reference count. This means that we don't have
         * to hold on to the geom handle, and may release it. The geom object
         * will be released automatically when the scene is destroyed.
         *
         * rtcAttachGeometry() returns a geometry ID. We could use this to
         * identify intersected objects later on.
         */
        rtcAttachGeometry(rtcScene, geom);
        rtcReleaseGeometry(geom);

        return true;
    }

    using namespace Alembic::AbcGeom;
    using namespace Alembic::AbcCoreFactory;

    void recurse(const IObject &object, Scene &scene) {

        ICompoundProperty props = object.getProperties();
        if (IPolyMeshSchema::matches(props.getHeader())) {
            IPolyMeshSchema meshSchema(props);
            IPolyMeshSchema::Sample meshSample;
            meshSchema.get(meshSample);
            P3fArraySamplePtr positions = meshSample.getPositions();
            Int32ArraySamplePtr indices = meshSample.getFaceIndices();
            N3fArraySamplePtr normals = meshSchema.getNormalsParam().getExpandedValue().getVals();

            printf("#     Loading %s : %zu points...\n", object.getName().c_str(),
                   positions->size());

            RTCGeometry geom = rtcNewGeometry(Bounce::GetGlobalDevice(),
                                              RTC_GEOMETRY_TYPE_TRIANGLE);

            auto *rtcVertices = (float *) rtcSetNewGeometryBuffer(geom,
                                                                  RTC_BUFFER_TYPE_VERTEX,
                                                                  0,
                                                                  RTC_FORMAT_FLOAT3,
                                                                  3 * sizeof(float),
                                                                  meshSample.getPositions()->size());

            auto *rtcIndices = (unsigned *) rtcSetNewGeometryBuffer(geom,
                                                                    RTC_BUFFER_TYPE_INDEX,
                                                                    0,
                                                                    RTC_FORMAT_UINT3,
                                                                    3 * sizeof(unsigned),
                                                                    indices->size() / 3);

            // Build embree buffers from abc mesh data
            Vec3f pos;
            if (rtcVertices) {
                for (size_t i = 0; i < positions->size(); i++) {
                    pos = positions->get()[i];
                    rtcVertices[i * 3] = pos.x;
                    rtcVertices[i * 3 + 1] = pos.y;
                    rtcVertices[i * 3 + 2] = pos.z;
                }
            }

            for (size_t i = 0; i < indices->size(); i++) {
                rtcIndices[i] = indices->get()[i];
            }

            rtcCommitGeometry(geom);
            rtcAttachGeometry(scene.rtcScene, geom);

            // Cleanup, the geometry is now attached to the scene, no need to keep it
            rtcReleaseGeometry(geom);
        }

        for (size_t i = 0; i < object.getNumChildren(); i++) {
            recurse(object.getChild(i), scene);
        }
    }

    void readAlembic(const std::string &filename, Scene &scene) {
        IArchive archive;
        IFactory factory;
        factory.setPolicy(Alembic::Abc::ErrorHandler::kNoisyNoopPolicy);
        IFactory::CoreType coreType;

        archive = factory.getArchive(filename, coreType);
        if (!archive.valid())
            return;

        IObject object = archive.getTop();
        recurse(object, scene);
    }

    Scene Scene::Open(const std::string &filename) {
        printf("# Loading %s...\n", filename.c_str());

        Scene scene;
        readAlembic(filename, scene);

        printf("# Done !\n");

        return scene;
    }

    Scene::Scene() {
        RTCDevice globalDevice = Bounce::GetGlobalDevice();
        BNC_ASSERT(globalDevice, "The global device is empty. "
                                 "Maybe try calling Bounce::InitializeBounce() first ?");

        rtcScene = rtcNewScene(globalDevice);
    }

}
