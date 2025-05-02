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

    int IsKeyDown(const Key& a_key) override;
    int IsKeyReleased( const Key& a_key) override;
    int IsKeyPressed(const Key& a_key) override;

    int IsMouseButtonDown(const MouseButton& a_button) override;
    int IsMouseButtonReleased(const MouseButton& a_button) override;
    int IsMouseButtonPressed(const MouseButton& a_button) override;

    inline Maths::Vector2 GetCursorPosition() override { return s_currentMousePos; }
    inline Maths::Vector2 GetMouseDelta() override { const Maths::Vector2 l_delta = s_currentMousePos - s_previousMousePos; const Maths::Vector2 l_result = l_delta; ResetMouseDelta(); return l_result; }
    inline Maths::Vector2 GetMouseScroll() override { const Maths::Vector2 l_returnVal = s_mouseScroll; s_mouseScroll = Maths::Vector2::Zero; return l_returnVal; }
    inline void ResetMouseDelta() override { s_previousMousePos = s_currentMousePos; };
    inline void SetCursorPosition(const double& a_xPos, const double& a_yPos) override { s_currentMousePos.x = static_cast<float>(a_xPos); s_currentMousePos.y = static_cast<float>(a_yPos); }
    inline void SetMouseScroll(const double& a_xAxis, const double& a_yAxis) override { s_mouseScroll.x = static_cast<float>(a_xAxis); s_mouseScroll.y = static_cast<float>(a_yAxis); }
    void ConfigureMouseInput(const CursorInputMode& a_cursorInputMode) override;

    GLFWInputManager* CastGLFW() override { return this; }


private:
    static void KeyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);
    static void MouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods);
    static void MouseScrollCallback(GLFWwindow* a_window, double a_xOffset, double a_yOffset);
    static void MouseCursorCallback(GLFWwindow* a_window, double a_xPos, double a_yPos);
    inline static void SetCursorPositionCallback(const double& a_xPos, const double& a_yPos) { s_currentMousePos.x = static_cast<float>(a_xPos); s_currentMousePos.y = static_cast<float>(a_yPos); s_previousMousePos = s_currentMousePos; }
    inline static void SetMouseScrollCallback(const double& a_xAxis, const double& a_yAxis) { s_mouseScroll.x = static_cast<float>(a_xAxis); s_mouseScroll.y = static_cast<float>(a_yAxis); }

    static std::array<int, 349> s_keyPressed;
    static std::array<Action, 349> s_keyStatus;

    static std::array<int, 12> s_mouseButtonPressed;
    static std::array<Action, 12> s_mouseButtonStatus;

    static Maths::Vector2 s_mouseScroll;
    static Maths::Vector2 s_currentMousePos;
    static Maths::Vector2 s_previousMousePos;

    GLFWwindow* m_window = nullptr;
};
