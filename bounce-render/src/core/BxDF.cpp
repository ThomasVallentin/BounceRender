//
// Created by tvallentin on 10/03/2022.
//

#include "BxDF.h"
#include "Sampling.h"

Color3f BxDF::Sample(const Vec3f &wo, Vec3f &wi, float &pdf) const {
    Vec2f u = RandomVector2<float>();
    wi = CosineHemisphereSample(u);
    // Flipping out if in is not oriented in the same direction as the normal
    if (wo.z < 0)
        wi.z *= -1;

    pdf = Pdf(wo, wi);
    return Evaluate(wo, wi);
}

float BxDF::Pdf(const Vec3f &wo, const Vec3f &wi) const {
    if (SameHemisphere(wo, wi))
        return AbsCosTheta(wi) * INV_PI;

    return 0.0f;
}
