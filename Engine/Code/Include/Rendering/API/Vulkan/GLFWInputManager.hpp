#pragma once

#include "IInputManager.hpp"

#include <array>

#include "GLFW/glfw3.h"

class IWindow;

class GLFWInputManager final : public IInputManager
{
public:
    void Initialize(IWindow* a_window) override;

    int IsKeyDown(IWindow* a_window, int a_key) override;
    int IsKeyUp(IWindow* a_window, int a_key) override;
    int IsKeyPressed(IWindow* a_window, int a_key) override;

    int IsMouseButtonDown(IWindow* a_window, int a_button) override;
    int IsMouseButtonUp(IWindow* a_window, int a_button) override;
    int IsMouseButtonPressed(IWindow* a_window, int a_button) override;

    Maths::Vector2 GetCursorPosition(IWindow* a_window) override;
    void SetCursorPosition(IWindow* a_window, Maths::Vector2 a_pos) override;

    Maths::Vector2 GetMouseScroll() override;
    void SetMouseScroll(Maths::Vector2 a_vec) override;

    GLFWInputManager* CastGLFW() override { return this; }

private:
    static void KeyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);
    static void MouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods);
    static void MouseScrollCallback(GLFWwindow* a_window, double a_xOffset, double a_yOffset);

    static std::array<int, 400> m_keyPressed;
    static std::array<int, 400> m_keyStatus;

    static std::array<int, 17> m_mouseButtonStatus;
    static std::array<int, 17> m_mouseButtonPressed;

    static std::array<int, 2> m_mouseScroll;

    GLFWwindow* m_window = nullptr;
};
