//
// Created by Thomas Vallentin on 22/06/2022.
//

#ifndef BOUNCE_RAY_H
#define BOUNCE_RAY_H


#include "Bounce.h"

#include <embree3/rtcore_ray.h>
#include <embree3/rtcore_common.h>


namespace Bounce {

    struct Ray {
        Ray() = default;

        Ray(const Vec3f& origin,
            const Vec3f& direction,
            const float& tnear = 0.0f,
            const float& tfar = FLT_MAX,
            const float& time = 0.0f,
            const unsigned int& mask = -1,
            const unsigned int& geomID = RTC_INVALID_GEOMETRY_ID,
            const unsigned int& primID = RTC_INVALID_GEOMETRY_ID)
                : origin(origin),
                direction(direction),
                tnear(tnear),
                tfar(tfar),
                time(time),
                mask(mask),
                geomID(geomID),
                primID(primID) {
            instID[0] = RTC_INVALID_GEOMETRY_ID;
        }

        // RTCRay attributes
        Vec3f origin;
        float tnear;

        Vec3f direction;
        float time = 0;

        float tfar;
        unsigned int mask;  // ray mask
        unsigned int id;    // ray ID
        unsigned int flags; // ray flags

        // RTCHit attributes
        Vec3f Ng;
        float u;
        float v;
        unsigned int primID;
        unsigned int geomID;
        unsigned int instID[RTC_MAX_INSTANCE_LEVEL_COUNT];
    };

    inline RTCRay* AsRTCRay(Ray& ray) {
        return (RTCRay*)&ray;
    }

    inline RTCRayHit* AsRTCRayHit(Ray& ray) {
        return (RTCRayHit*)&ray;
    }

    inline Vec3f ComputeHitPoint(const Ray& ray) { return ray.origin + ray.direction * ray.tfar; }

}

#endif //BOUNCE_RAY_H
