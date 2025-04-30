#pragma once

#include "IInputManager.hpp"

#include "Camera.hpp"


class CameraEditor : public Camera
{
public:
    CameraEditor() = default;
    ~CameraEditor() override = default;

    void Init(const float& a_aspectRatio, const float& a_fov, const float& a_nearPlane, const float& a_farPlane);
    void Update(float a_aspectRatio);

    void UpdateInput(IWindow* a_window, IInputManager* a_input);

    [[nodiscard]] float GetMovementSpeed() const { return m_movementSpeed; }
    [[nodiscard]] float GetRotationSpeed() const { return m_rotationSpeed; }
    [[nodiscard]] float GetCameraSpeed() const { return m_cameraSpeed; }
    [[nodiscard]] float GetAspectRatio() const { return m_aspectRatio; }
    [[nodiscard]] float GetFOV() const { return m_fov; }
    [[nodiscard]] float GetNearPlane() const { return m_nearPlane; }
    [[nodiscard]] float GetFarPlane() const { return m_farPlane; }
    [[nodiscard]] Maths::Matrix4 GetViewMatrix() const { return m_viewMatrix; }
    [[nodiscard]] Maths::Matrix4 GetProjectionMatrix() const { return m_projectionMatrix; }

    void SetMovementSpeed(const float a_speed) { m_movementSpeed = a_speed; };
    void SetRotationSpeed(const float a_speed) { m_rotationSpeed = a_speed; };
    void SetCameraSpeed(const float a_speed) { m_cameraSpeed = a_speed; };
    void SetFOV(const float a_fov) { m_fov = a_fov; };
    void SetNearPlane(const float a_nearPlane) { m_nearPlane = a_nearPlane; };
    void SetFarPlane(const float a_farPlane) { m_farPlane = a_farPlane; };
    void SetAspectRatio(const float a_ratio) { m_aspectRatio = a_ratio; };


private:
    void MovementHandler(IWindow* a_window, IInputManager* a_input, float a_movementSpeed);
    void MouseHandler(IWindow* a_window, IInputManager* a_input);
    void SpeedHandler(IWindow* a_window, IInputManager* a_input, const float& a_cameraSpeed, float& a_movementSpeed);

    Maths::Matrix4 m_projectionMatrix { Maths::Matrix4::identity };
    Maths::Matrix4 m_viewMatrix { Maths::Matrix4::identity };

    Maths::Vector3 m_eye { Maths::Vector3(0.0f, 0.0f, 3.0f) };
    Maths::Vector3 m_center { Maths::Vector3(0.0f, 0.0f, 0.0f) };
    Maths::Vector3 m_up { Maths::Vector3(0.0f, 1.0f, 0.0f) };
    Maths::Vector3 m_velocity { Maths::Vector3(0.0f, 0.0f, 0.0f) };
    Maths::Vector3 m_right { Maths::Vector3::YAxis };
    Maths::Vector3 m_forward { Maths::Vector3::YAxis };

    float m_movementSpeed { 1.0f };
    float m_rotationSpeed { 1.0f };
    float m_cameraSpeed { 0.1f };
    float m_aspectRatio { 800.0f / 600.0f };
    float m_fov { 1.f };
    float m_nearPlane { 1.f };
    float m_farPlane { 1.f };
};

