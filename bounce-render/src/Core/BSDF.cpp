//
// Created by tvallentin on 10/03/2022.
//

#include "BSDF.h"
#include "Ray.h"
#include "BxDF.h"
#include "Random.h"

namespace Bounce {

    BSDF::BSDF(const Ray &ray) :
            worldToLocal(Imath::extractQuat(Imath::rotationMatrix(ray.Ng,
                                                                  Vec3f(0, 0, 1)))) {}


    Vec3f BSDF::WorldToLocal(const Vec3f &vec) const {
        return worldToLocal.rotateVector(vec);
    }

    Vec3f BSDF::LocalToWorld(const Vec3f &vec) const {
        return worldToLocal.inverse().rotateVector(vec);
    }

    Color3f BSDF::Sample(const Vec3f &woWorld, Vec3f &wiWorld, float &pdf) const {

        // Choose random bxdf
        int sampledIndex = RandomInteger<int>(0, bxdfCount - 1);
        BxDF *sampledBxdf = bxdfs[sampledIndex];

        // Sample the choosen bxdf
        Vec3f wi, wo = WorldToLocal(woWorld);

        pdf = 0;
        Color3f f = sampledBxdf->Sample(wo, wi, pdf);

        // Evaluate the current sample on all the other bxdf
//    for (int i = 0; i < bxdfCount; i++) {
//        BxDF *bxdf = bxdfs[i];
//        if (bxdf == sampledBxdf) {
//            continue;
//        }
//        pdf += bxdf->Pdf(in, out);
//        f += bxdf->Evaluate(in, out);
//    }

        wiWorld = LocalToWorld(wi);
        return f;
    }

}