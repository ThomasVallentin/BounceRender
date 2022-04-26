//
// Created by tvallentin on 10/03/2022.
//

#ifndef BOUNCE_LAMBERTIAN_H
#define BOUNCE_LAMBERTIAN_H

#include "Core/Bounce.h"
#include "Core/BxDF.h"

namespace Bounce {

    class Lambertian : public BxDF {
    public:
        Lambertian() : Kd(0.5f) {}

        explicit Lambertian(const Color3f &Kd) : Kd(Kd) {}

        Color3f Evaluate(const Vec3f &in, const Vec3f &out) const override;

    private:
        Color3f Kd;
    };

}

#endif //BOUNCE_LAMBERTIAN_H
