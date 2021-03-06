//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "Camera.h"
#include "Rebound/Core/Logging.h"
#include "Rebound/Core/Inputs.h"
#include "Rebound/Core/Notifier.h"

namespace Rebound {

    Camera::Camera(const float &fov, const float &aspectRatio, const float &nearClip,
                   const float &farClip)
            : m_fov(fov),
              m_aspectRatio(aspectRatio),
              m_nearClip(nearClip),
              m_farClip(farClip) {
        UpdateProjection();
        UpdateView();
    }

    void Camera::OnUpdate() {
        glm::vec2 mousePos = Input::GetMousePosition();

        // Only editing the camera when alt is pressed
        if (Input::IsKeyPressed(KeyCode::Left_alt)) {
            glm::vec2 delta = mousePos - m_prevMousePos;

            if (Input::IsMouseButtonPressed(MouseButton::ButtonMiddle))
                MousePan(delta.x, delta.y);
            else if (Input::IsMouseButtonPressed(MouseButton::ButtonLeft))
                MouseRotate(delta.x, delta.y);
            else if (Input::IsMouseButtonPressed(MouseButton::ButtonRight))
                MouseZoom(delta.x);
        }

        m_prevMousePos = mousePos;
    }

    void Camera::MousePan(const float &deltaX, const float &deltaY) {
        m_focalPoint -= GetSideDirection() * deltaX * 3.0f * m_distance / m_viewportWidth;
        m_focalPoint += GetUpDirection() * deltaY * 3.0f * m_distance / m_viewportWidth;

        UpdateView();
    }

    void Camera::MouseRotate(const float &deltaX, const float &deltaY) {
        m_yaw -= deltaX * 0.01f;
        m_pitch -= deltaY * 0.01f;
        UpdateView();
    }

    void Camera::MouseZoom(const float &deltaX) {
        m_distance -= deltaX * 0.003f * m_distance;
        UpdateView();
    }

    void Camera::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUNC(Camera::OnMouseScrollEvent));
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(Camera::OnKeyPressedEvent));
    }

    bool Camera::OnMouseScrollEvent(MouseScrolledEvent &event) {
        m_distance -= event.GetOffsetY() * 0.3f * m_distance;

        UpdateView();

        return false;
    }

    bool Camera::OnKeyPressedEvent(KeyPressedEvent &event) {
        // Pseudo focus that reset the camera distance and focal point
        if (event.GetKey() == KeyCode::F) {
            m_focalPoint = {0.0f, 0.0f, 0.0f};
            m_distance = 5.0f;
            m_pitch = -0.5f;
            m_yaw = 0.5f;

            UpdateView();
        }

        return false;
    }

    void Camera::SetViewportSize(const float &width, const float &height) {
        m_viewportWidth = width;
        m_viewportHeight = height;
        m_aspectRatio = m_viewportWidth / m_viewportHeight;
        UpdateProjection();
    }

    glm::vec3 Camera::GetForwardDirection() const {
        return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
    }

    glm::vec3 Camera::GetUpDirection() const {
        return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::vec3 Camera::GetSideDirection() const {
        return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
    }

    glm::quat Camera::GetOrientation() const {
        return {glm::vec3(m_pitch, m_yaw, m_roll) };
    }

    glm::vec3 Camera::ComputePosition() const {
        return m_focalPoint - GetForwardDirection() * m_distance;
    }

    void Camera::UpdateView() {
        auto oldMatrix = m_viewMatrix;

        m_position = ComputePosition();
        glm::quat orientation = GetOrientation();
        m_viewMatrix = glm::translate(glm::mat4(1.0f), m_position) * glm::toMat4(orientation);
        m_viewMatrix = glm::inverse(m_viewMatrix);

        if (oldMatrix != m_viewMatrix) {
            Notifier<Camera *>::Notify(this, new Notice);
        }
    }

    void Camera::UpdateProjection() {
        auto oldMatrix = m_projectionMatrix;

        m_projectionMatrix = glm::perspective(glm::radians(m_fov),
                                              m_aspectRatio,
                                              m_nearClip,
                                              m_farClip);

        if (oldMatrix != m_projectionMatrix) {
            Notifier<Camera *>::Notify(this, new Notice);
        }
    }

    float Camera::GetFov() const {
        return m_fov;
    }

    glm::vec3 Camera::GetEulerAngles() const {
        return {m_pitch, m_yaw, m_roll};
    }

    DEFINE_NOTIFIER_SENDER_TYPE(Camera*);

}
