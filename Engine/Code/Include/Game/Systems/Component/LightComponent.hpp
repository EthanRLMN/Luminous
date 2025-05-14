#pragma once

#include "EntityComponent.hpp"

#include "Vector3.hpp"


constexpr unsigned int MAX_LIGHTS = 32;


struct alignas(16) LightData
{
    alignas(16) Maths::Vector3 m_position { 0.0f, 0.0f, 0.0f };
    alignas(16) Maths::Vector3 m_direction { 0.0f, 0.0f, -1.0f };
    alignas(16) Maths::Vector3 m_color { 1.0f, 1.0f, 1.0f };
    int m_type { 0 };
    float m_intensity { 1.0f };
    float m_ambientStrength { 0.0f };
    float m_specularStrength { 0.5f };
    int m_count { 2 };
};

class LightComponent : public EntityComponent
{
public:
    void Initialize() override{};
    void GameplayStarted() override{};
    void Update() override{};

    LightData& GetLight() { return light; };

    void SetLight(const Maths::Vector3& position,
             const Maths::Vector3& direction,
             const Maths::Vector3& color,
             int type,
             float intensity,
             float ambientStrength,
             float specularStrength,
             int count)
    {
        light.m_position = position;
        light.m_direction = direction;
        light.m_color = color;
        light.m_type = type;
        light.m_intensity = intensity;
        light.m_ambientStrength = ambientStrength;
        light.m_specularStrength = specularStrength;
        light.m_count = count;
    }
private:
    LightData light{};
};
