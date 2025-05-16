#pragma once

#include "Vector3.hpp"
#include "Utils/LightUtils.hpp"


struct alignas(16) LightData
{
    alignas(16) Maths::Vector3 m_position { 0.0f, 0.0f, 0.0f };
    alignas(16) Maths::Vector3 m_direction { 0.0f, 0.0f, -1.0f };
    alignas(16) Maths::Vector3 m_color { 1.0f, 1.0f, 1.0f };

    LightType m_type { LightType::POINT };
    float m_intensity { 1.0f };
    float m_ambientStrength { 0.0f };
    float m_specularStrength { 0.5f };
};


struct alignas(16) GpuLightBuffer
{
    alignas(16) int m_lightCount { 0 };

    LightData m_lights[MAX_LIGHTS];
};