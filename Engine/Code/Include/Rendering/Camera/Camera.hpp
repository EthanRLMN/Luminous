#pragma once

#include "Vector3.hpp"
#include "Matrix4.hpp"

class Camera
{
public:
    Camera() {};
    ~Camera() {};


protected:
    void UpdateProjectionMatrix();
    void UpdateViewMatrix();  


    //Windows aspect , Need to be changed to match the actual Window 
    float aspectRatio = 800.0f / 600.0f;


private:
    Maths::Matrix4 m_projectionMatrix = Maths::Matrix4::identity;
    Maths::Matrix4 m_viewMatrix = Maths::Matrix4::identity;
 
    Maths::Vector3 m_position = Maths::Vector3::One;
    Maths::Vector3 m_direction = Maths::Vector3::One;
    Maths::Vector3 m_up = Maths::Vector3::One;

    float fov{ 1.f };
    float nearPlane{1.f};
    float farPlane{1.f};


};

