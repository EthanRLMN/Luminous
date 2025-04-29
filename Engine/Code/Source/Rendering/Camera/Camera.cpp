#include "Rendering/Camera/Camera.hpp"


Maths::Matrix4 Camera::UpdateProjectionMatrix() const
{
    return Maths::Matrix4::Perspective(fov, aspectRatio, nearPlane, farPlane);
}

Maths::Matrix4 Camera::UpdateViewMatrix() const
{
    return Maths::Matrix4::LookAt(m_position,m_position - m_direction, m_up);
}


Maths::Matrix4 Camera::UpdateProjectionMatrixCustom(float a_fov,float a_aspectRatio,float a_nearPlane, float a_farPlane) const
{
    return Maths::Matrix4::Perspective(a_fov, a_aspectRatio, a_nearPlane, a_farPlane);
}

Maths::Matrix4 Camera::UpdateViewMatrixCustom(Maths::Vector3 a_position, Maths::Vector3 a_direction , Maths::Vector3 a_up) const
{
    return Maths::Matrix4::LookAt(a_position, a_direction, a_up);
}
