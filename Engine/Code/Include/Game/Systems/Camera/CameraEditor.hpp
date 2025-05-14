#pragma once

#include "IInputManager.hpp"

#include "Camera.hpp"


class CameraEditor : public Camera
{
public:
    CameraEditor() = default;
    ~CameraEditor() override = default;

    void Init(float a_aspectRatio, float a_fov, float a_nearPlane, float a_farPlane);
    void Update(float a_aspectRatio);
    void UpdateInput(IInputManager* a_input);

    [[nodiscard]] float GetMovementSpeed() const { return m_movementSpeed; }
    [[nodiscard]] float GetRotationSpeed() const { return m_rotationSpeed; }
    [[nodiscard]] float GetCameraSpeed() const { return m_speedMultiplier; }
    [[nodiscard]] float GetAspectRatio() const { return m_aspectRatio; }
    [[nodiscard]] float GetFOV() const { return m_fov; }
    [[nodiscard]] float GetNearPlane() const { return m_nearPlane; }
    [[nodiscard]] float GetFarPlane() const { return m_farPlane; }
    [[nodiscard]] float GetMouseSensitivity() const { return m_mouseSensitivity; }
    [[nodiscard]] float GetYaw() const { return m_yaw; }
    [[nodiscard]] float GetPitch() const { return m_pitch; }
    [[nodiscard]] float GetSpeedMultiplier() const { return m_speedMultiplier; }

    [[nodiscard]] Maths::Vector3 GetEye() const { return m_eye; }
    [[nodiscard]] Maths::Vector3 GetCenter() const { return m_center; }
    [[nodiscard]] Maths::Vector3 GetWorldRight() const { return m_worldRight; }
    [[nodiscard]] Maths::Vector3 GetWorldUp() const { return m_worldUp; }
    [[nodiscard]] Maths::Vector3 GetWorldForward() const { return m_worldForward; }
    [[nodiscard]] Maths::Vector3 GetLocalRight() const { return m_localRight; }
    [[nodiscard]] Maths::Vector3 GetLocalUp() const { return m_localUp; }
    [[nodiscard]] Maths::Vector3 GetLocalForward() const { return m_localForward; }
    [[nodiscard]] Maths::Matrix4 GetViewMatrix() const { return m_viewMatrix; }
    [[nodiscard]] Maths::Matrix4 GetProjectionMatrix() const { return m_projectionMatrix; }

    void SetMovementSpeed(const float a_speed) { m_movementSpeed = a_speed; };
    void SetRotationSpeed(const float a_speed) { m_rotationSpeed = a_speed; };
    void SetCameraSpeed(const float a_speed) { m_speedMultiplier = a_speed; };
    void SetFOV(const float a_fov) { m_fov = a_fov; };
    void SetNearPlane(const float a_nearPlane) { m_nearPlane = a_nearPlane; };
    void SetFarPlane(const float a_farPlane) { m_farPlane = a_farPlane; };
    void SetAspectRatio(const float a_ratio) { m_aspectRatio = a_ratio; };
    void SetMouseSensitivity(const float a_sensitivity) { m_mouseSensitivity = a_sensitivity; };
    void SetYaw(const float a_yaw) { m_yaw = a_yaw; };
    void SetPitch(const float a_pitch) { m_pitch = a_pitch; };
    void SetSpeedMultiplier(const float a_multiplier) { m_speedMultiplier = a_multiplier; };
    void SetEye(const Maths::Vector3& a_eye) { m_eye = a_eye; };
    void SetCenter(const Maths::Vector3& a_center) { m_center = a_center; };
    void SetWorldRight(const Maths::Vector3& a_right) { m_worldRight = a_right; };
    void SetWorldUp(const Maths::Vector3& a_up) { m_worldUp = a_up; };
    void SetWorldForward(const Maths::Vector3& a_forward) { m_worldForward = a_forward; };
    void SetLocalRight(const Maths::Vector3& a_right) { m_localRight = a_right; };
    void SetLocalUp(const Maths::Vector3& a_up) { m_localUp = a_up; };
    void SetLocalForward(const Maths::Vector3& a_forward) { m_localForward = a_forward; };
    void SetViewMatrix(const Maths::Matrix4& a_viewMatrix) { m_viewMatrix = a_viewMatrix; };


private:
    void MovementHandler(IInputManager* a_input);
    void RotationHandler(IInputManager* a_input);
    void SpeedHandler(IInputManager* a_input);
    void TriggerMouseRotation(IInputManager* a_input);
    void UpdateVectors();

    static Maths::Vector3 GetForwardFromYawPitch(float a_yawDegrees, float a_pitchDegrees);

    Maths::Matrix4 m_projectionMatrix { Maths::Matrix4::identity };
    Maths::Matrix4 m_viewMatrix { Maths::Matrix4::identity };
    Maths::Vector3 m_eye { 0.0f, 0.0f, 5.0f };
    Maths::Vector3 m_center { 0.0f, 0.0f, 4.0f };

    Maths::Vector3 m_worldRight { Maths::Vector3::XAxis };
    Maths::Vector3 m_worldUp { Maths::Vector3::YAxis };
    Maths::Vector3 m_worldForward { Maths::Vector3::ZAxis };

    Maths::Vector3 m_localRight { m_worldRight };
    Maths::Vector3 m_localUp { m_worldUp };
    Maths::Vector3 m_localForward { m_worldForward };

    float m_baseSpeed { 1.0f };
    float m_dynamicSpeed { m_baseSpeed };
    float m_movementSpeed { m_baseSpeed };
    float m_rotationSpeed { 1.0f };
    float m_speedMultiplier { 0.25f };
    float m_aspectRatio { 800.0f / 600.0f };
    float m_fov { 60.0f };
    float m_nearPlane { 0.1f };
    float m_farPlane { 100.f };
    float m_yaw { -90.0f };
    float m_pitch { 0.0f };
    float m_mouseSensitivity { 10.0f };
    bool m_isRotating { false };
};

