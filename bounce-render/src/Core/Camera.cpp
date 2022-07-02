//
// Created by Thomas Vallentin on 30/06/2022.
//

#include "Camera.h"
#include "Sampling.h"

namespace Bounce {

    ThinLensCamera::ThinLensCamera() :
            // Default camera uses a 35mm Academy film gate
            ThinLensCamera({}, {640, 360}, {21.946, 16.002}, 35, 1, 0) {}

    ThinLensCamera::ThinLensCamera(const Mat4f &transform,
                                   const Vec2f &resolution,
                                   const Vec2f &filmGate,
                                   const float &focalLength,
                                   const float &focusDistance,
                                   const float &apertureRadius)
                : Camera(transform),
                  m_apertureRadius(apertureRadius),
                  m_focusDistance(focusDistance) {
        float fDist = fmaxf(focusDistance, 0.001);
        float halfFov = atanf(filmGate.x / (2 * focalLength));
        float focusPlaneWidth = 2 * fDist * tanf(halfFov);
        float focusPlaneHeight = resolution.y / resolution.x * focusPlaneWidth;
        m_projectionPlane = {focusPlaneWidth, focusPlaneHeight};
    }

    float ThinLensCamera::Sample(const Vec2f &uv, Ray& ray) const {
        Vec2f topLeftCorner = m_projectionPlane * Vec2f(-0.5, 0.5);
        Vec3f focusPoint = {topLeftCorner.x + uv.x * m_projectionPlane.x,
                            topLeftCorner.y - uv.y * m_projectionPlane.y,
                            -m_focusDistance};

        // Sample lens
        Vec3f origin(0.0f, 0.0f, 0.0f);
        if (m_apertureRadius > 0) {
            Vec2f randomPointOnLens = ConcentricDiskSample() * m_apertureRadius;
            origin = {randomPointOnLens.x, randomPointOnLens.y, 0};
        }

        Vec3f dir = (focusPoint - origin).normalized();

        // Computing world space origin and direction
        GetTransform().multDirMatrix(dir, dir) ;
        GetTransform().multVecMatrix(origin, origin);

        ray = Ray(origin, dir, m_nearClip, m_farClip);

        // Simple implementation, aperture do not influence the amount of received light
        return 1.0f;
    }

}
