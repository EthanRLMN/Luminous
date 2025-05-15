#pragma once

#include "Game/Systems/Camera/Camera.hpp"

class CameraComponent : public Camera
{
public:
    CameraComponent() = default;

    bool GetisActive() { return m_isActive; }
    float GetNearPlane() { return m_nearPlane; }
    float GetFarPlane() { return m_farPlane; }
    float GetFieldOfView() { return m_fieldOfView; }

    void SetIsActive(bool a_isActive) { m_isActive = a_isActive; }
    void SetNearPlane(float a_nearPlane) { m_nearPlane = a_nearPlane; }
    void SetFarPlane(float a_farPlane) { m_farPlane = a_farPlane; }
    void SetFieldOfView(float a_fieldofView) { m_fieldOfView = a_fieldofView; }

private: 

    bool m_isActive;
    float m_nearPlane;
    float m_farPlane;
    float m_fieldOfView
};
