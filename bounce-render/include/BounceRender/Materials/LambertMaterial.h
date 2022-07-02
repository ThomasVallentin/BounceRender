//
// Created by tvallentin on 11/03/2022.
//

#ifndef BOUNCE_LAMBERTMATERIAL_H
#define BOUNCE_LAMBERTMATERIAL_H

#include "BounceRender/Core/Material.h"

namespace Bounce {

    class LambertMaterial : public Material {
    public:
        LambertMaterial() : diffuseColor(1.0f) {}

        explicit LambertMaterial(const Color3f &diffuseColor) : diffuseColor(diffuseColor) {}

        void FillBSDF(const Ray &ray, BSDF &bsdf) const override;

    private:
        Color3f diffuseColor;
    };

}

#endif //BOUNCE_LAMBERTMATERIAL_H
