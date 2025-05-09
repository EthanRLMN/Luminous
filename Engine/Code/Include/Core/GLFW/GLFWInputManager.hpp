#pragma once

#include <array>

#include "GLFWWindow.hpp"
#include "GLFW/glfw3.h"

#include "IInputManager.hpp"

class IWindow;

inline static constexpr std::array<int, 4> glfwCursorInputType = {
    GLFW_CURSOR_NORMAL,
    GLFW_CURSOR_HIDDEN,
    GLFW_CURSOR_DISABLED,
    GLFW_CURSOR_CAPTURED
};


inline auto operator<=>(Key lhs, const int rhs)
{
    return static_cast<int>(lhs) <=> rhs;
}

class GLFWInputManager final : public IInputManager
{
public:
    static int CastGlfwInput(const CursorInputMode& a_cursorInputMode);

    void Initialize(IWindow* a_window) override;
    void Destroy(IWindow* a_window) override;
    void Update() override;

    [[nodiscard]] int IsKeyDown(const Key& a_key) const override;
    [[nodiscard]] int IsKeyReleased( const Key& a_key) const override;
    [[nodiscard]] int IsKeyPressed(const Key& a_key) const override;

    [[nodiscard]] int IsMouseButtonDown(const MouseButton& a_button) const override;
    [[nodiscard]] int IsMouseButtonReleased(const MouseButton& a_button) const override;
    [[nodiscard]] int IsMouseButtonPressed(const MouseButton& a_button) const override;

    [[nodiscard]] inline Maths::Vector2 GetCursorPosition() const override { return s_currentMousePos; }
    [[nodiscard]] inline Maths::Vector2 GetMouseDelta() const override { const Maths::Vector2 l_delta = s_currentMousePos - s_previousMousePos; const Maths::Vector2 l_result = l_delta; return l_result; }
    [[nodiscard]] inline Maths::Vector2 GetMouseScroll() const override { const Maths::Vector2 l_returnVal = s_mouseScroll; s_mouseScroll = Maths::Vector2::Zero; return l_returnVal; }
    inline void ResetMouseDelta() override { s_previousMousePos = s_currentMousePos; };
    inline void SetCursorPosition(const double& a_xPos, const double& a_yPos) override { s_currentMousePos.x = static_cast<float>(a_xPos); s_currentMousePos.y = static_cast<float>(a_yPos); }
    inline void SetMouseScroll(const double& a_xAxis, const double& a_yAxis) override { s_mouseScroll.x = static_cast<float>(a_xAxis); s_mouseScroll.y = static_cast<float>(a_yAxis); }
    inline void ConfigureMouseInput(const CursorInputMode& a_cursorInputMode) override { glfwSetInputMode(m_window->GetGLFWWindow(), GLFW_CURSOR, CastGlfwInput(a_cursorInputMode)); };

    GLFWInputManager* CastGLFW() override { return this; }


private:
    static void KeyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);
    static void MouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods);
    static void MouseScrollCallback(GLFWwindow* a_window, double a_xOffset, double a_yOffset);
    static void MouseCursorCallback(GLFWwindow* a_window, double a_xPos, double a_yPos);
    inline static void SetCursorPositionCallback(const double& a_xPos, const double& a_yPos) { s_currentMousePos.x = static_cast<float>(a_xPos); s_currentMousePos.y = static_cast<float>(a_yPos); }
    inline static void SetMouseScrollCallback(const double& a_xAxis, const double& a_yAxis) { s_mouseScroll.x = static_cast<float>(a_xAxis); s_mouseScroll.y = static_cast<float>(a_yAxis); }
    inline static bool IsKeyValid(const int a_key) { return a_key >= 0 && a_key < static_cast<int>(s_keyPressed.size()); }
    inline static bool IsKeyValid(const Key a_key) { return a_key >= 0 && a_key < static_cast<int>(s_keyPressed.size()); }


    static std::array<int, LUMINOUS_KEY_LAST> s_keyPressed;
    static std::array<Action, LUMINOUS_KEY_LAST> s_keyStatus;

    static std::array<int, LUMINOUS_MOUSE_BUTTON_LAST> s_mouseButtonPressed;
    static std::array<Action, LUMINOUS_MOUSE_BUTTON_LAST> s_mouseButtonStatus;

    static Maths::Vector2 s_mouseScroll;
    static Maths::Vector2 s_currentMousePos;
    static Maths::Vector2 s_previousMousePos;

    GLFWWindow* m_window = nullptr;
};
