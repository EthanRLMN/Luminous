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
    static void MouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods);

    Vector2 GetCursorPosition(IWindow* a_window) override;
    void SetCursorPosition(IWindow* a_window, Vector2 a_pos) override;

    GLFWInputManager* CastGLFW() override { return this; }

private:
    inline static int m_keyPressed[400];
    inline static int m_keyStatus[400];

    inline static int m_mouseButtonStatus[16];
    inline static int m_mouseButtonPressed[16];

    //std::vector<int> m_keyStatus;
};
    static void KeyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);

	static std::array<int, 400> m_keyPressed;
	static std::array<int, 400> m_keyStatus;
};
