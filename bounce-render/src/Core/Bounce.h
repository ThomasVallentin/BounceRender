//
// Created by tvallentin on 10/03/2022.
//

#ifndef BOUNCE_H
#define BOUNCE_H

#define PI_2 1.57079632679
#define PI_4 0.78539816339
#define INV_PI 0.31830988618
#define INV_2_PI 0.15915494309

#include "embree3/rtcore.h"
#include "ImathVec.h"
#include "ImathVecAlgo.h"
#include "ImathColor.h"
#include "ImathQuat.h"
#include "ImathMatrix.h"
#include "ImathMatrixAlgo.h"

namespace Bounce {

    typedef Imath::V2i Vec2i;
    typedef Imath::V2f Vec2f;
    typedef Imath::V3f Vec3f;
    typedef Imath::V4f Vec4f;
    typedef Imath::C3f Color3f;
    typedef Imath::Quatf Quatf;
    typedef Imath::M33f Mat3f;
    typedef Imath::M44f Mat4f;

    extern RTCDevice g_globalDevice;

    extern bool InitializeBounce();
    extern void ReleaseBounce();
    extern RTCDevice GetGlobalDevice();

    struct Ray;
    class BSDF;
    class BxDF;
    class Material;
    class Camera;
    class Scene;

    inline float CosTheta(const Vec3f &vec) { return vec.z; }
    inline float AbsCosTheta(const Vec3f &vec) { return std::abs(vec.z); }
    inline bool SameHemisphere(const Vec3f &v1, const Vec3f &v2) { return v1.z * v2.z > 0; }

}

#endif //BOUNCE_H
