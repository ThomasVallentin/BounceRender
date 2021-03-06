//
// Created by tvallentin on 11/03/2022.
//

#include "LambertMaterial.h"
#include "Bxdfs/Lambertian.h"

namespace Bounce {

    void LambertMaterial::FillBSDF(const Ray &ray, BSDF &bsdf) const {
        bsdf.AddBxDF(new Lambertian(diffuseColor));
    }

}
