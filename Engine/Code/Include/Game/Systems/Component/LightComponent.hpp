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
private:
    LightData light{};
};
