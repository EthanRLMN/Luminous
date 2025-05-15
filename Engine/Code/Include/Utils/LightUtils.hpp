#pragma once

// Define the max number of lights in a scene
constexpr unsigned int MAX_LIGHTS { 64 };


enum class LightType : unsigned int
{
    DIRECTIONAL = 0,
    POINT = 1,
    COUNT
};