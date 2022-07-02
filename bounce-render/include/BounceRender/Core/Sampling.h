//
// Created by tvallentin on 11/03/2022.
//

#ifndef BOUNCE_SAMPLING_H
#define BOUNCE_SAMPLING_H

#include "Random.h"
#include "Bounce.h"

namespace Bounce {

    // Disk sampling
    Vec2f ConcentricDiskSample(const Vec2f &sample);
    Vec2f ConcentricDiskSample();
    float ConcentricDiskPdf();

    // Hemisphere sampling

    Vec3f UniformHemisphereSample(const Vec2f &sample);
    float UniformHemispherePdf();

    Vec3f CosineHemisphereSample(const Vec2f &sample);
    float CosineHemispherePdf(const float &cosTheta);

}

#endif //BOUNCE_SAMPLING_H
