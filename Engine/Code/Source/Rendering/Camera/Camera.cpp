#include "Rendering/Camera/Camera.hpp"


Maths::Matrix4 Camera::UpdateProjectionMatrix() const
{
    return Maths::Matrix4::Perspective(fov, aspectRatio, nearPlane, farPlane);
}

Maths::Matrix4 Camera::UpdateViewMatrix() const
{
    return Maths::Matrix4::LookAt(m_position, m_direction, m_up);
}
