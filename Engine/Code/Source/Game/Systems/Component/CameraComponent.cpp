#include "Game/Systems/Component/CameraComponent.hpp"

void CameraComponent::Initialize() {

    m_worldForward = (m_center - m_eye).Normalize();
    m_worldRight = m_worldForward.CrossProduct(m_worldUp).Normalize();
    m_worldUp = m_worldRight.CrossProduct(m_worldForward).Normalize();

    m_projectionMatrix = UpdateProjectionMatrix(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);
}

void CameraComponent::Update() {
    m_viewMatrix = UpdateViewMatrix(m_eye, m_center, m_worldUp);
}

