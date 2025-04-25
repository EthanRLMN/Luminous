#pragma once

#include "Vector3.hpp"
#include "Matrix4.hpp"

class Camera
{
public:
    Camera() {};
    ~Camera() {};

    void UpdateProjectionMatrix();
    void UpdateViewMatrix();  

private:
    Maths::Matrix4 m_projectionMatrix = Maths::Matrix4::identity;
    Maths::Matrix4 m_viewMatrix = Maths::Matrix4::identity;
 
    Maths::Vector3 m_position;
    Maths::Vector3 m_direction;
    Maths::Vector3 m_up;

    float fov;
    float nearPlane;
    float farPlane;

};

