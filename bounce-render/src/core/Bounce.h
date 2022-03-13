//
// Created by tvallentin on 10/03/2022.
//

#ifndef BOUNCE_H
#define BOUNCE_H

#define INV_PI 0.31830988618
#define INV_2_PI 0.15915494309

#include "embree3/rtcore.h"
#include "ImathVec.h"
#include "ImathVecAlgo.h"
#include "ImathColor.h"
#include "ImathQuat.h"
#include "ImathMatrix.h"
#include "ImathMatrixAlgo.h"

typedef Imath::V2f Vec2f;
typedef Imath::V3f Vec3f;
typedef Imath::C3f Color3f;
typedef Imath::Quatf Quatf;
typedef Imath::M44f Mat4f;

class BSDF;
class BxDF;
class Material;

inline float CosTheta(const Vec3f &vec) { return vec.z; }
inline float AbsCosTheta(const Vec3f &vec) { return std::abs(vec.z); }
inline bool SameHemisphere(const Vec3f &v1, const Vec3f &v2) { return v1.z * v2.z > 0; }

inline Vec3f RayDir(const RTCRay &ray) { return Vec3f(ray.dir_x, ray.dir_y, ray.dir_z); }
inline Vec3f RayDir(const RTCRayHit &rayhit) { return RayDir(rayhit.ray); }
inline Vec3f RayOrigin(const RTCRay &ray) { return Vec3f(ray.org_x, ray.org_y, ray.org_z); }
inline Vec3f RayOrigin(const RTCRayHit &rayhit) { return RayOrigin(rayhit.ray); }
inline Vec3f HitNormal(const RTCHit &hit) { return Vec3f(hit.Ng_x, hit.Ng_y, hit.Ng_z); }
inline Vec3f HitNormal(const RTCRayHit &rayhit) { return HitNormal(rayhit.hit); }
inline Vec3f HitPoint(const RTCRay &ray) { return RayOrigin(ray) + RayDir(ray) * ray.tfar; }
inline Vec3f HitPoint(const RTCRayHit &rayhit) { return HitPoint(rayhit.ray); }
inline RTCRay CreateRay(const Vec3f &org, const Vec3f &dir) {
    RTCRay ray;

    ray.org_x = org.x; ray.org_y = org.y; ray.org_z = org.z;
    ray.dir_x = dir.x; ray.dir_y = dir.y; ray.dir_z = dir.z;

    ray.tnear = 0; ray.tfar = std::numeric_limits<float>::infinity();
    ray.mask = -1;
    ray.flags = 0;

    return ray;
}

inline RTCRayHit CreateRayHit(const Vec3f &org, const Vec3f &dir) {
    RTCHit hit;
    hit.geomID = RTC_INVALID_GEOMETRY_ID;
    hit.instID[0] = RTC_INVALID_GEOMETRY_ID;
    return RTCRayHit{CreateRay(org, dir), hit};
}

#endif //BOUNCE_H
