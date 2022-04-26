//
// Created by tvallentin on 10/03/2022.
//

#ifndef BOUNCE_BXDF_H
#define BOUNCE_BXDF_H


#include "Bounce.h"

namespace Bounce {

    class BxDF {
    public:
        BxDF() = default;

        virtual Color3f Sample(const Vec3f &wo, Vec3f &wi, float &pdf) const;
        virtual float Pdf(const Vec3f &wo, const Vec3f &wi) const;
        virtual Color3f Evaluate(const Vec3f &wo, const Vec3f &wi) const = 0;
    };

}

#endif //BOUNCE_BXDF_H
