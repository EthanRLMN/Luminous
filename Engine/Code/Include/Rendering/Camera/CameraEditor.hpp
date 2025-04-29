#pragma once

#include "IInputManager.hpp"

#include "Camera.hpp"


class CameraEditor : public Camera
{
public:
    CameraEditor() = default;
    ~CameraEditor() = default;

    void Init(IWindow* a_window, const float& a_aspectRatio, const float& a_fov, const float& a_nearPlane, const float& a_farPlane);
    void Update();

    void UpdateInput(IWindow* a_window, IInputManager* a_input);

    [[nodiscard]] float GetMovementSpeed() const { return m_movementSpeed; }

    void SetAspectRatio(const float a_ratio) { aspectRatio = a_ratio; };

    Maths::Matrix4 m_projectionMatrix{ Maths::Matrix4::identity };
    Maths::Matrix4 m_viewMatrix{ Maths::Matrix4::identity };

private:
    void MovementHandler(IWindow* a_window, IInputManager* a_input, float a_movementSpeed);
    void RotationHandler(IWindow* a_window, IInputManager* a_input);
    void SpeedHandler(IWindow* a_window, IInputManager* a_input, const float& a_cameraSpeed, float& a_movementSpeed);

    Maths::Vector3 m_camPosition{ Maths::Vector3(-2.0f, 0.0f, 0.0f) };
    Maths::Vector3 m_camDirection{ Maths::Vector3::One };
    Maths::Vector3 m_camUp{ Maths::Vector3::ZAxis };
    Maths::Vector3 m_camForward{ m_camDirection.Normalize() };

    float m_movementSpeed{ 1.0f };
    float m_rotationSpeed{ 1.0f };
    float m_cameraSpeed{ 0.1f };
};

