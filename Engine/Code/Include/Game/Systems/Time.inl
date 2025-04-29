#pragma once

#include <chrono>


class Time
{
public:
    /**
     * @brief Function used to update the DeltaTime and the FixedDeltaTime
     */
    inline static void Update()
    {
        UpdateDeltaTime();
        UpdateFixedDeltaTime();
    }

    /**
     * @brief Function used to run an update based on the FixedDeltaTime
     * @return Whether the update has been performed or not
     */
    inline static bool FixedUpdate()
    {
        if (s_accumulator >= s_fixedDeltaTime)
        {
            s_accumulator -= s_fixedDeltaTime;
            return true;
        }
        return false;
    }

    /**
     * @brief Function used to reset all timers (Last Time, Total Time Elapsed and Accumulator)
     */
    inline static void Reset()
    {
        ResetLastTime();
        ResetTotalTimeElapsed();
        ResetAccumulator();
    }

    /**
     * @brief Function used to reset the Last Time
     */
    inline static void ResetLastTime() { s_lastTime = std::chrono::steady_clock::now(); }

    /**
     * @brief Function used to reset the Total Time Elapsed
     */
    inline static void ResetTotalTimeElapsed() { s_totalTimeElapsed = 0.0; }

    /**
     * @brief Function used to reset the Accumulator
     */
    inline static void ResetAccumulator() { s_accumulator = 0.0f; }


    /**
     * @brief Getter for the DeltaTime
     * @return The delta time (in seconds)
     */
    inline static float GetDeltaTime() noexcept { return s_deltaTime; }

    /**
     * @brief Getter for the DeltaTime
     * @return The delta time (in seconds)
     */
    inline static float GetAccumulator() noexcept { return s_accumulator; }

    /**
     * @brief Getter for the FixedDeltaTime
     * @return The fixed delta time (in seconds)
     */
    inline static float GetFixedDeltaTime() noexcept { return s_fixedDeltaTime; }

    /**
     * @brief Getter for the ScaledDeltaTime
     * @return The scaled delta time (in seconds)
     */
    inline static float GetScaledDeltaTime() noexcept { return s_deltaTime * s_timeScale; }

    /**
     * @brief Getter for the Interpolation Alpha
     * @return The interpolation alpha (in seconds)
     */
    inline static float GetInterpolationAlpha() noexcept { return s_accumulator / s_fixedDeltaTime; }

    /**
     * @brief Getter for the Time Scale
     * @return The timescale (1.0f = default)
     */
    inline static float GetTimeScale() noexcept { return s_timeScale; }

    /**
     * @brief Getter for the Frames Per Second
     * @return The current FPS value
     */
    inline static float GetFPS() noexcept { return s_deltaTime > 0.0001f ? 1.0f / s_deltaTime : 0.0f; }

    /**
     * @brief Getter for the TotalTimeElapsed
     * @return The elapsed time (in seconds) since the beginning of the program (unless it has been reset since)
     */
    inline static double GetTotalTimeElapsed() noexcept { return s_totalTimeElapsed; }

    /**
     * @brief Getter for the current TimeScale value
     * @return True if the game is paused (timescale == 0.0f), False otherwise
     */
    inline static bool IsPaused() noexcept { return s_timeScale == 0.0f; }

    /**
     * @brief A setter for the DeltaTime
     * @param a_newDeltaTime The value of the new DeltaTime
     */
    inline static void SetFixedDeltaTime(const float a_newDeltaTime) { s_fixedDeltaTime = a_newDeltaTime > s_minFixedDeltaTime ? a_newDeltaTime : s_minFixedDeltaTime; s_accumulator = 0.0f; }

    /**
     * @brief A setter for the TimeScale
     * @param a_newTimeScale The value of the new TimeScale (Min = 0.0f, Max = 100.0f)
     */
    inline static void SetTimeScale(const float a_newTimeScale) { s_timeScale = std::clamp(a_newTimeScale, 0.0f, 100.0f); }

    /**
     * @brief A getter for the current game pause status
     * @param a_isPaused Whether the game should be paused or not
     */
    inline static void SetPaused(const bool a_isPaused)
    {
        if (a_isPaused)
        {
            if (!IsPaused())
            {
                s_previousTimeScale = s_timeScale;
                s_timeScale = 0.0f;
            }
        }
        else if (IsPaused())
            s_timeScale = s_previousTimeScale;
    }

    /**
     * @brief Calcultates the number of physic passes
     * @return The number of physics passes to run (0 if not necessary0
     */
    inline static int CalculatePhysicsPasses()
    {
        const int l_steps = static_cast<int>(s_accumulator / s_fixedDeltaTime);
        const int l_clampedSteps = std::min(l_steps, s_maxPhysicsPasses);

        s_accumulator -= l_clampedSteps * s_fixedDeltaTime;
        return l_clampedSteps;
    }


private:
    inline static void UpdateDeltaTime()
    {
        const std::chrono::high_resolution_clock::time_point l_currentTimePoint = std::chrono::high_resolution_clock::now();
        const double l_delta = std::chrono::duration<double>(l_currentTimePoint - s_lastTime).count();

        s_deltaTime = static_cast<float>(l_delta);
        s_lastTime = l_currentTimePoint;

        const double l_scaledDelta = l_delta * s_timeScale;
        s_totalTimeElapsed += l_scaledDelta;
    }

    inline static void UpdateFixedDeltaTime()
    {
        UpdateAccumulator();
    }

    inline static void UpdateAccumulator()
    {
        s_accumulator += s_deltaTime * s_timeScale;
        if (s_accumulator > s_maxFrameTime)
            s_accumulator = s_maxFrameTime;
    }

    inline static constexpr int s_maxPhysicsPasses { 4 }; // Max amount of physic passes per frame
    inline static constexpr float s_maxFrameTime { 0.25f }; // Clamp max frametime value, useful to avoid a potential "spiral of death": https://gafferongames.com/post/fix_your_timestep/
    inline static constexpr float s_minFixedDeltaTime { 0.001f }; // Min fixed delta time value

    inline static float s_timeScale { 1.0f }; // Useful for pauses or slow-motion
    inline static float s_previousTimeScale { 1.0f } ; // Store the previous timescale
    inline static float s_fixedDeltaTime { 1.0f / 60.0f }; // ≈ 0.0166667f | Unity uses 0.02f as an example. May use a double for more precision
    inline static float s_deltaTime { 0.0f };
    inline static float s_accumulator { 0.0f }; // Captures the time elapsed, useful to ensure physics update are made properly

    inline static double s_totalTimeElapsed { 0.0 }; // Captures the total time elapsed since the beginning of the program. Useful for timers

    inline static std::chrono::high_resolution_clock::time_point s_lastTime { std::chrono::high_resolution_clock::now() };
};
