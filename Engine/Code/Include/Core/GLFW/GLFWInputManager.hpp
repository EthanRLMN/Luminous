#pragma once

#include <array>

#include "GLFW/glfw3.h"

#include "IInputManager.hpp"

class IWindow;

static constexpr std::array<int, 4> glfwCursorInputType = {
    GLFW_CURSOR_NORMAL,
    GLFW_CURSOR_HIDDEN,
    GLFW_CURSOR_DISABLED,
    GLFW_CURSOR_CAPTURED
};

static int CastGlfwInput(const CursorInputMode& a_cursorInputMode)
{
    const int l_cursorInputIndex = static_cast<int>(a_cursorInputMode);
    return glfwCursorInputType[l_cursorInputIndex];
}

class GLFWInputManager final : public IInputManager
{
public:
    void Initialize(IWindow* a_window) override;
    void Destroy(IWindow* a_window) override;
    void Update(IWindow* a_window) override {};

    int IsKeyDown(IWindow* a_window, const Key& a_key) override;
    int IsKeyUp(IWindow* a_window, const Key& a_key) override;
    int IsKeyPressed(IWindow* a_window, const Key& a_key) override;

    int IsMouseButtonDown(IWindow* a_window, const MouseButton& a_button) override;
    int IsMouseButtonUp(IWindow* a_window, const MouseButton& a_button) override;
    int IsMouseButtonPressed(IWindow* a_window, const MouseButton& a_button) override;

    inline Maths::Vector2 GetCursorPosition(IWindow* a_window) override { return m_currentMousePos; }
    inline Maths::Vector2 GetMouseDelta(IWindow* a_window) override
    {
        const Maths::Vector2 l_delta = m_currentMousePos - m_previousMousePos; SetCursorPosition(0.0, 0.0); m_previousMousePos = m_currentMousePos; return l_delta.Normalize();
    }
    inline Maths::Vector2 GetMouseScroll() override { const Maths::Vector2 l_returnVal = m_mouseScroll; m_mouseScroll = Maths::Vector2::Zero; return l_returnVal; }

    inline static void SetCursorPosition(const double& a_xPos, const double& a_yPos) { m_currentMousePos.x = static_cast<float>(a_xPos); m_currentMousePos.y = static_cast<float>(a_yPos); }
    inline static void SetMouseScroll(const double& a_xAxis, const double& a_yAxis) { m_mouseScroll.x = static_cast<float>(a_xAxis); m_mouseScroll.y = static_cast<float>(a_yAxis); }

    void ConfigureMouseInput(const CursorInputMode& a_cursorInputMode) override;

    GLFWInputManager* CastGLFW() override { return this; }


private:
    static void KeyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);
    static void MouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods);
    static void MouseScrollCallback(GLFWwindow* a_window, double a_xOffset, double a_yOffset);
    static void MouseCursorCallback(GLFWwindow* a_window, double a_xPos, double a_yPos);

    static std::array<int, 349> m_keyPressed;
    static std::array<Action, 349> m_keyStatus;

    static std::array<int, 12> m_mouseButtonPressed;
    static std::array<Action, 12> m_mouseButtonStatus;

    static Maths::Vector2 m_mouseScroll;
    static Maths::Vector2 m_currentMousePos;
    static Maths::Vector2 m_previousMousePos;

    GLFWwindow* m_window = nullptr;
};
