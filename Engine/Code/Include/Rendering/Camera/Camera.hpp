#pragma once

#include "Vector3.hpp"
#include "Matrix4.hpp"

class Camera
{
public:
    Camera() {};
    ~Camera() {};

protected:
    Maths::Matrix4 UpdateProjectionMatrix() const;
    Maths::Matrix4 UpdateViewMatrix() const;

    Maths::Matrix4 UpdateProjectionMatrixCustom(float a_fov, float a_aspectRatio, float a_nearPlane, float a_farPlane) const;
    Maths::Matrix4 UpdateViewMatrixCustom(Maths::Vector3 a_position, Maths::Vector3 a_direction, Maths::Vector3 a_up) const;
 


    float aspectRatio = 800.0f / 600.0f;
    float fov{ 1.f };
    float nearPlane{1.f};
    float farPlane{1.f};

    Maths::Vector3 m_position = Maths::Vector3::One;
    Maths::Vector3 m_direction = Maths::Vector3::One;
    Maths::Vector3 m_up = Maths::Vector3::One;

};

