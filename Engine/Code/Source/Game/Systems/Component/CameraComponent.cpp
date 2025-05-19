#include "Game/Systems/Component/CameraComponent.hpp"

#include "Engine.hpp"

void CameraComponent::Initialize()
{
    m_worldForward = (m_center - m_eye).Normalize();
    m_worldRight = m_worldForward.CrossProduct(m_worldUp).Normalize();
    m_worldUp = m_worldRight.CrossProduct(m_worldForward).Normalize();

    m_projectionMatrix = UpdateProjectionMatrix(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);

    ForceSetMainCamera(false);
}

void CameraComponent::Update()
{
    if (TransformComponent* l_transform = GetOwner()->GetComponent<TransformComponent>().get())
    {
        if (l_transform->GetGlobalPosition() != m_oldOwnerTransform)
        {
            m_oldOwnerTransform = l_transform->GetGlobalPosition();
            m_eye = m_oldOwnerTransform;
            m_center = m_eye + Maths::Vector3(0, 0, -1) * l_transform->GetGlobalRotationQuat();
        }
    }
    m_viewMatrix = UpdateViewMatrix(m_eye, m_center, m_worldUp);
}