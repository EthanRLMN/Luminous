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

    [[nodiscard]] int IsKeyDown(const Key& a_key) override;
    [[nodiscard]] int IsKeyReleased( const Key& a_key) override;
    [[nodiscard]] int IsKeyPressed(const Key& a_key) override;

    [[nodiscard]] int IsMouseButtonDown(const MouseButton& a_button) override;
    [[nodiscard]] int IsMouseButtonReleased(const MouseButton& a_button) override;
    [[nodiscard]] int IsMouseButtonPressed(const MouseButton& a_button) override;

    [[nodiscard]] inline Maths::Vector2 GetCursorPosition() const override { return m_currentMousePos; }
    [[nodiscard]] inline Maths::Vector2 GetMouseDelta() const override { const Maths::Vector2 l_delta = m_currentMousePos - m_previousMousePos; const Maths::Vector2 l_result = l_delta; return l_result; }
    [[nodiscard]] inline Maths::Vector2 GetMouseScroll() override { const Maths::Vector2 l_returnVal = m_mouseScroll; m_mouseScroll = Maths::Vector2::Zero; return l_returnVal; }
    inline void ResetMouseDelta() override { m_previousMousePos = m_currentMousePos; };
    inline void SetCursorPosition(const double& a_xPos, const double& a_yPos) override { m_currentMousePos.x = static_cast<float>(a_xPos); m_currentMousePos.y = static_cast<float>(a_yPos); }
    inline void SetMouseScroll(const double& a_xAxis, const double& a_yAxis) override { m_mouseScroll.x = static_cast<float>(a_xAxis); m_mouseScroll.y = static_cast<float>(a_yAxis); }
    inline void ConfigureMouseInput(const CursorInputMode& a_cursorInputMode) override { glfwSetInputMode(m_window->GetGLFWWindow(), GLFW_CURSOR, CastGlfwInput(a_cursorInputMode)); };

    GLFWInputManager* CastGLFW() override { return this; }


private:
    static void KeyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);
    static void MouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods);
    static void MouseScrollCallback(GLFWwindow* a_window, double a_xOffset, double a_yOffset);
    static void MouseCursorCallback(GLFWwindow* a_window, double a_xPos, double a_yPos);

    void OnKey(int a_key, int a_scancode, int a_action, int a_mods);
    void OnMouseButton(int a_button, int a_action, int a_mods);
    void OnScroll(double a_xOffset, double a_yOffset);
    void OnCursorPos(double a_xPos, double a_yPos);

    inline void SetCursorPositionCallback(const double& a_xPos, const double& a_yPos) { m_currentMousePos.x = static_cast<float>(a_xPos); m_currentMousePos.y = static_cast<float>(a_yPos); }
    inline void SetMouseScrollCallback(const double& a_xAxis, const double& a_yAxis) { m_mouseScroll.x = static_cast<float>(a_xAxis); m_mouseScroll.y = static_cast<float>(a_yAxis); }
    [[nodiscard]] inline bool IsKeyValid(const int a_key) const { return a_key >= 0 && a_key < static_cast<int>(m_keyPressed.size()); }
    [[nodiscard]] inline bool IsKeyValid(const Key a_key) const { return a_key >= 0 && a_key < static_cast<int>(m_keyPressed.size()); }


    std::array<int, LUMINOUS_KEY_LAST> m_keyPressed {};
    std::array<Action, LUMINOUS_KEY_LAST> m_keyStatus {};

    std::array<int, LUMINOUS_MOUSE_BUTTON_LAST> m_mouseButtonPressed {};
    std::array<Action, LUMINOUS_MOUSE_BUTTON_LAST> m_mouseButtonStatus {};

    Maths::Vector2 m_mouseScroll { Maths::Vector2::Zero };
    Maths::Vector2 m_currentMousePos { Maths::Vector2::Zero };
    Maths::Vector2 m_previousMousePos { Maths::Vector2::Zero };

    GLFWWindow* m_window { nullptr };
};
