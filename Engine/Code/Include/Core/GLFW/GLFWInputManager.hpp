#pragma once

#include <array>

#include "GLFW/glfw3.h"

#include "IInputManager.hpp"

class IWindow;


class GLFWInputManager final : public IInputManager
{
public:
    void Initialize(IWindow* a_window) override;
    void Destroy(IWindow* a_window) override;
    void Update(IWindow* a_window) override;

    int IsKeyDown(IWindow* a_window, Key a_key) override;
    int IsKeyUp(IWindow* a_window, Key a_key) override;
    int IsKeyPressed(IWindow* a_window, Key a_key) override;

    int IsMouseButtonDown(IWindow* a_window, MouseButton a_button) override;
    int IsMouseButtonUp(IWindow* a_window, MouseButton a_button) override;
    int IsMouseButtonPressed(IWindow* a_window, MouseButton a_button) override;

    Maths::Vector2 GetCursorPosition(IWindow* a_window) override;
    void SetCursorPosition(IWindow* a_window, Maths::Vector2 a_pos) override;

    Maths::Vector2 GetMouseScroll() override;


    void SetMouseScroll(Maths::Vector2 a_vec) override
    {
    };

    GLFWInputManager* CastGLFW() override { return this; }


private:
    static void KeyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);
    static void MouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods);
    static void MouseScrollCallback(GLFWwindow* a_window, double a_xOffset, double a_yOffset);

    static std::array<int, 349> m_keyPressed;
    static std::array<Action, 349> m_keyStatus;

    static std::array<int, 12> m_mouseButtonPressed;
    static std::array<Action, 12> m_mouseButtonStatus;

    static std::array<int, 2> m_mouseScroll;

    GLFWwindow* m_window = nullptr;
};
