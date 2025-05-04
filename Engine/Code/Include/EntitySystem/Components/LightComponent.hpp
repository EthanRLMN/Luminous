#pragma once

#include "EntitySystem/EntityComponent.hpp"

#include "Quaternion.hpp"
#include "Vector3.hpp"


#define MAX_LIGHTS 32;



class LightComponent : public EntityComponent
{
public:
    void Create() override{};
    void Destroy() override{};
    void Update() override{};

    Maths::Vector3 m_position = Maths::Vector3(1.0f, 0.0f, 0.0f);
    alignas(16) Maths::Vector3 m_direction = Maths::Vector3(0.0f, 0.0f, 0.0f);
    alignas(16) Maths::Vector3 m_color = Maths::Vector3(1.0f, 1.0f, 1.0f);
    alignas(4) uint32_t m_type = 0;
    alignas(4) float m_intensity = 1.0f;
};
