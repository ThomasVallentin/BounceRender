//
// Created by tvallentin on 10/03/2022.
//

#ifndef BOUNCE_BSDF_H
#define BOUNCE_BSDF_H

#include <vector>

#include "embree3/rtcore_ray.h"

#include "Bounce.h"

namespace Bounce {

    class BSDF {
    public:
        explicit BSDF(const RTCRayHit &rayhit) :
                worldToLocal(Imath::extractQuat(Imath::rotationMatrix(HitNormal(rayhit),
                                                                      Vec3f(0, 0, 1)))) {}

        void AddBxDF(BxDF *bxdf) {
            bxdfs[bxdfCount++] = bxdf;
        }

        Color3f Sample(const Vec3f &wo, Vec3f &wi, float &pdf) const;

        Vec3f WorldToLocal(const Vec3f &vec) const;

        Vec3f LocalToWorld(const Vec3f &vec) const;

    private:
        // TODO: Optimize this
        Quatf worldToLocal;
        static const int maxBxdfs = 8;
        int bxdfCount = 0;
        BxDF *bxdfs[maxBxdfs];
    };

}

#endif //BOUNCE_BSDF_H
