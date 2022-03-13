//
// Created by tvallentin on 08/03/2022.
//

#ifndef BOUNCE_MATERIAL_H
#define BOUNCE_MATERIAL_H

#include "Bounce.h"
#include "BSDF.h"

class RTCRayHit;

class Material {
public:
    Material() = default;

    virtual void FillBSDF(const RTCRayHit &rayhit, BSDF &bsdf) const = 0;
};


#endif //BOUNCE_MATERIAL_H
