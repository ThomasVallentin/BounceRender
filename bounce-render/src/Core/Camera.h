//
// Created by Thomas Vallentin on 30/06/2022.
//

#ifndef BOUNCE_CAMERA_H
#define BOUNCE_CAMERA_H


#include "Ray.h"


namespace Bounce {

    class Camera {
    public:
        Camera() : m_transform() {}
        Camera(const Mat4f &transform) : m_transform(transform) {}

        virtual float Sample(const Vec2f &uv, Ray& ray) const = 0;

        inline const Mat4f& GetTransform() const { return m_transform; }

    private:
        Mat4f m_transform;
    };

    class ThinLensCamera : public Camera {
    public:
        ThinLensCamera();
        ThinLensCamera(const Mat4f &transform,
                       const Vec2f &resolution,
                       const Vec2f &filmGate,
                       const float &focalLength,
                       const float &focusDistance = 0.001,
                       const float &aperture = 0);

        float Sample(const Vec2f &uv, Ray &ray) const override;

    private:
        float m_apertureRadius;
        Vec2f m_projectionPlane;
        float m_focusDistance;

        float m_nearClip = 0.01, m_farClip = FLT_MAX;
    };

}

#endif //BOUNCE_CAMERA_H
