#pragma once

#include <array>
#include "IInputManager.hpp"
#include "GLFW/glfw3.h"
#include "Utils/Exporter.hpp"


class IWindow;

class GLFWInputManager final : public IInputManager
{
public:
    LUMINOUS_ENGINE_API void Initialize(IWindow* a_window) override;
    LUMINOUS_ENGINE_API void Destroy(IWindow* a_window) override;
    LUMINOUS_ENGINE_API void Update(IWindow* a_window) override;

    LUMINOUS_ENGINE_API int IsKeyDown(IWindow* a_window, Key a_key) override;
    LUMINOUS_ENGINE_API int IsKeyUp(IWindow* a_window, Key a_key) override;
    LUMINOUS_ENGINE_API int IsKeyPressed(IWindow* a_window, Key a_key) override;

    LUMINOUS_ENGINE_API int IsMouseButtonDown(IWindow* a_window, MouseButton a_button) override;
    LUMINOUS_ENGINE_API int IsMouseButtonUp(IWindow* a_window, MouseButton a_button) override;
    LUMINOUS_ENGINE_API int IsMouseButtonPressed(IWindow* a_window, MouseButton a_button) override;

    LUMINOUS_ENGINE_API Maths::Vector2 GetCursorPosition(IWindow* a_window) override;
    LUMINOUS_ENGINE_API void SetCursorPosition(IWindow* a_window, Maths::Vector2 a_pos) override;

    LUMINOUS_ENGINE_API Maths::Vector2 GetMouseScroll() override;
    LUMINOUS_ENGINE_API void SetMouseScroll(Maths::Vector2 a_vec) = 0;

    LUMINOUS_ENGINE_API GLFWInputManager* CastGLFW() override { return this; }

private:
    static void KeyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);
    static void MouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods);
    static void MouseScrollCallback(GLFWwindow* a_window, double a_xOffset, double a_yOffset);

    static std::array<int, 400> m_keyPressed;
    static std::array<Action, 400> m_keyStatus;

    static std::array<Action, 17> m_mouseButtonStatus;
    static std::array<int, 17> m_mouseButtonPressed;

    static std::array<int, 2> m_mouseScroll;

    GLFWwindow* m_window = nullptr;
};
