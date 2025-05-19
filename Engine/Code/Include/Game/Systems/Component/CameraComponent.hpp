#pragma once
#include "EntityComponent.hpp"
#include "Quaternion.hpp"
#include "Game/Systems/Camera/Camera.hpp"

class CameraComponent : public Camera, public EntityComponent
{
public:
    CameraComponent() = default;

    void Initialize() override;
    void GameplayStarted() override {};
    void Update() override ;
  

    bool IsActive() const { return m_isActive; }
    float GetNearPlane() const { return m_nearPlane; }
    float GetFarPlane() const { return m_farPlane; }
    float GetFieldOfView() const { return m_fieldOfView; }
    float GetAspectRatio() const { return m_aspectRatio; }
    bool GetIsMainCamera() const { return m_mainCamera; }

    Maths::Vector3 GetEye() const { return m_eye; }
    Maths::Vector3 GetCenter() const { return m_center; }

    void SetIsActive(const bool a_isActive) { m_isActive = a_isActive; }
    void SetNearPlane(const float a_nearPlane) { m_nearPlane = a_nearPlane; }
    void SetFarPlane(const float a_farPlane) { m_farPlane = a_farPlane; }
    void SetFieldOfView(const float a_fieldofView) { m_fieldOfView = a_fieldofView; }
    void SetAspectRatio(const float a_aspectRatio) { m_aspectRatio = a_aspectRatio; }
    void SetEye(const Maths::Vector3 a_eye){m_eye = a_eye;}
    void SetCenter(const Maths::Vector3 a_center) {m_center = a_center;}
    void ForceSetMainCamera(const bool a_val) { m_mainCamera = a_val; }

    [[nodiscard]] Maths::Matrix4 GetViewMatrix() const { return m_viewMatrix; }
    [[nodiscard]] Maths::Matrix4 GetProjectionMatrix() const { return m_projectionMatrix; }

private:
    bool m_isActive { true };
    bool m_mainCamera { false };
    float m_aspectRatio { 800.0f / 600.0f };
    float m_nearPlane { 0.1f };
    float m_farPlane { 1000.f };
    float m_fieldOfView{ 80.0f };

    Maths::Vector3 m_oldOwnerTransform { 0.0f };
    Maths::Quaternion m_oldOwnerRot{ Maths::Quaternion::Identity };

    Maths::Matrix4 m_projectionMatrix { Maths::Matrix4::identity };
    Maths::Matrix4 m_viewMatrix { Maths::Matrix4::identity };

    Maths::Vector3 m_eye { 0.0f, 0.0f, 5.0f };
    Maths::Vector3 m_center { 0.0f, 0.0f, 4.0f };

    Maths::Vector3 m_worldRight { Maths::Vector3::XAxis };
    Maths::Vector3 m_worldUp { Maths::Vector3::YAxis };
    Maths::Vector3 m_worldForward { Maths::Vector3::ZAxis };
};
