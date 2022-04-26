//
// Created by tvallentin on 10/03/2022.
//

#include "Lambertian.h"


namespace Bounce {

    Color3f Lambertian::Evaluate(const Vec3f &in, const Vec3f &out) const {
        return Kd * INV_PI;
    }

}
