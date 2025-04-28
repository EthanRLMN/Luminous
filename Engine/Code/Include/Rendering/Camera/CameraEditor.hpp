#pragma once

#include "IInputManager.hpp"

#include "Camera.hpp"


class CameraEditor : public Camera
{
public:
    CameraEditor() = default;
    ~CameraEditor() = default;

    void Init(IWindow* a_window, float a_aspectRatio, float a_fov, float a_nearPlane, float a_farPlane);
    void Update();

    void UpdateInput(IWindow* a_window, IInputManager* a_input);

    [[nodiscard]] float GetMovementSpeed() const { return m_movementSpeed; }

    void SetAspectRatio(float a_ratio) { aspectRatio = a_ratio; };

    Maths::Matrix4 m_projectionMatrix { Maths::Matrix4::identity };
    Maths::Matrix4 m_viewMatrix { Maths::Matrix4::identity };

private:
    Maths::Vector3 m_camPosition { Maths::Vector3(2.0f, 2.0f, 2.0f) };
    Maths::Vector3 m_camDirection { Maths::Vector3::One };
    Maths::Vector3 m_camUp { Maths::Vector3::ZAxis };

    float m_movementSpeed { 0.0001f };
};

