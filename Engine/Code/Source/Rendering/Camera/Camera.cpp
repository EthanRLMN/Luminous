#include "Rendering/Camera/Camera.hpp"


Maths::Matrix4 Camera::UpdateProjectionMatrix()
{
    return Maths::Matrix4::Perspective(fov, aspectRatio, nearPlane, farPlane);
}

Maths::Matrix4 Camera::UpdateViewMatrix()
{
    //Maths::Vector3 l_cameraPointLookAt = m_position + m_direction;
    return Maths::Matrix4::LookAt(m_position, m_position + m_direction, m_up);
}
