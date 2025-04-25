#pragma once

#include "Vector3.hpp"
#include "Matrix4.hpp"

class Camera
{
public:
    Camera() {};
    ~Camera() {};

protected:
    Maths::Matrix4 UpdateProjectionMatrix();
    Maths::Matrix4 UpdateViewMatrix(); 


    float aspectRatio = 800.0f / 600.0f;
    float fov{ 1.f };
    float nearPlane{1.f};
    float farPlane{1.f};

    Maths::Vector3 m_position = Maths::Vector3::One;
    Maths::Vector3 m_direction = Maths::Vector3::One;
    Maths::Vector3 m_up = Maths::Vector3::One;

};

