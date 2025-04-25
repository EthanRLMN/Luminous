#include "Rendering/Camera/Camera.hpp"


void Camera::UpdateProjectionMatrix(){
    m_projectionMatrix = Maths::Matrix4::Perspective(fov, aspectRatio, nearPlane, farPlane);
}

void Camera::UpdateViewMatrix()
{
    Maths::Vector3 l_cameraPointLookAt = m_position + m_direction;
    m_viewMatrix = Maths::Matrix4::LookAt(m_position, l_cameraPointLookAt, m_up);
}
