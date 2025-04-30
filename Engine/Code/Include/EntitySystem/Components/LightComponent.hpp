#pragma once

#include "EntitySystem/EntityComponent.hpp"

#include "Quaternion.hpp"
#include "Vector3.hpp"


class LightComponent : public EntityComponent
{
public:
    void Create() override {};
    void Destroy() override {};
    void Update() override {};

    Maths::Vector3 m_position = Maths::Vector3::Zero;
    Maths::Vector3 m_direction = Maths::Vector3::Zero;
    float m_intensity = 1.0f;
};
