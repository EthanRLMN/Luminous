#pragma once

#include "EntitySystem/EntityComponent.hpp"

#include "Quaternion.hpp"
#include "Vector3.hpp"


//constexpr unsigned int MAX_LIGHTS = 32;

struct alignas(16) LightData
{
    alignas(16) Maths::Vector3 m_position{ 1.0f, 1.0f, 0.0f };
    alignas(16) Maths::Vector3 m_direction { 1.0f, 0.0f, 1.0f };
    alignas(16) Maths::Vector3 m_color { 1.0f, 1.0f, 1.0f };
    int m_type = 1;
    float m_intensity = 1.0;
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
