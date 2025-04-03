#pragma once

class TimeSystem
{
public:
    float DeltaTime() const { return m_deltaTime; }
    float FixedDeltaTime() const { return m_fixedDeltaTime; }
    float TimeScale() const { return m_timeScale; }
    float SmoothDeltaTime() const { return m_smoothDeltaTime; }


private:
    float m_deltaTime { 0.f };
    float m_fixedDeltaTime { 0.002f };
    float m_timeScale = { 1.f };
    float m_smoothDeltaTime = { 0.f};
};
