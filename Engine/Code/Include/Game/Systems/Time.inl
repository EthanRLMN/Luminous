#pragma once
#include <chrono>

class Time
{
public:
    inline static void Update()
    {

    }

    inline static float GetDeltaTime() { return s_deltaTime; }


private:
    inline static float s_deltaTime{ 0.0f };
    inline static std::chrono::high_resolution_clock::time_point s_lastTime{ std::chrono::high_resolution_clock::now() };
};
