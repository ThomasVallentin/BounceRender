//
// Created by tvallentin on 11/03/2022.
//

#include "Sampling.h"


// From GI Compendium (34)
Vec3f UniformHemisphereSample(const Vec2f &sample) {
    float z = sample.y;
    float u = std::sqrt(std::max(0.0f, 1.0f - z * z));
    float phi = M_PI * 2 * sample.x;

    return Vec3f(std::cos(phi) * u, std::sin(phi) * u, z);
}

float UniformHemispherePdf() {
    return INV_2_PI;
}

// From Shirley & Chiu "A Low Distortion Map Between Disk and Square"
Vec2f ConcentricDiskSample(const Vec2f &sample) {
    Vec2f u = sample * 2 - Vec2f(1.0f, 1.0f);

    if (u.x == 0 && u.y == 0)
        return Vec2f(0, 0);

    float r, theta;

    // Comparing squared values instead of absolutes
    if (u.x*u.x > u.y*u.y) {
        r = u.x;
        theta = M_PI_4 * (u.x / u.y);
    } else {
        r = u.y;
        theta = M_PI_2 - M_PI_4 * (u.x / u.y);
    }

    return r * Vec2f(std::cos(theta), std::sin(theta));
}

// From GI Compendium (35)
Vec3f CosineHemisphereSample(const Vec2f &sample) {
    Vec2f u = ConcentricDiskSample(sample);
    float z = std::sqrt(std::max(0.0f, 1 - u.x * u.x - u.y * u.y));
    return Vec3f(u.x, u.y, z);
}

float CosineHemispherePdf(const float &cosTheta) {
    return cosTheta * INV_PI;
}
