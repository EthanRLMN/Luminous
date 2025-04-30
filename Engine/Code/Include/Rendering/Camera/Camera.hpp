#pragma once

#include "Matrix4.hpp"
#include "Vector3.hpp"

class Camera
{
public:
    virtual ~Camera() = default;

    [[nodiscard]] inline Maths::Matrix4 UpdateProjectionMatrix(const float& a_fov, const float& a_aspectRatio, const float& a_nearPlane, const float& a_farPlane) { return Maths::Matrix4::Perspective(a_fov, a_aspectRatio, a_nearPlane, a_farPlane); }
    [[nodiscard]] inline Maths::Matrix4 UpdateViewMatrix(const Maths::Vector3& a_position, const Maths::Vector3& a_direction, const Maths::Vector3& a_up) { return Maths::Matrix4::LookAt(a_position, a_direction, a_up); }
};

