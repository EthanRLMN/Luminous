#pragma once

#include <array>
#include <unordered_map>

#include "IInputManager.hpp"

#include "GLFWWindow.hpp"
#include "GLFW/glfw3.h"

#include "Game/Systems/Input/InputAction.hpp"


class IWindow;


inline static constexpr std::array<int, 4> glfwCursorInputType = {
    GLFW_CURSOR_NORMAL,
    GLFW_CURSOR_HIDDEN,
    GLFW_CURSOR_DISABLED,
    GLFW_CURSOR_CAPTURED
};


inline auto operator<=>(Key a_leftSign, const int a_rightSign) { return static_cast<int>(a_leftSign) <=> a_rightSign; }


class GLFWInputManager final : public IInputManager
{
public:
    static int CastGlfwInput(const CursorInputMode& a_cursorInputMode);

    void Initialize(IWindow* a_window) override;
    void Destroy(IWindow* a_window) override {};
    void Update() override;

    [[nodiscard]] int IsKeyDown(const Key& a_key) const override;
    [[nodiscard]] int IsKeyReleased( const Key& a_key) const override;
    [[nodiscard]] int IsKeyPressed(const Key& a_key) override;
    [[nodiscard]] int IsMouseButtonDown(const MouseButton& a_button) override;
    [[nodiscard]] int IsMouseButtonReleased(const MouseButton& a_button) override;
    [[nodiscard]] int IsMouseButtonPressed(const MouseButton& a_button) override;
    [[nodiscard]] bool IsShortcutPressed(const Key& a_key, int a_requiredMods, bool a_allowRepeat) override;
    [[nodiscard]] bool IsActionPressed(const std::string& a_actionName) const override;
    [[nodiscard]] bool IsActionDown(const std::string& a_actionName) const override;
    [[nodiscard]] bool IsActionReleased(const std::string& a_actionName) const override;
    [[nodiscard]] inline Maths::Vector2 GetCursorPosition() const override { return m_currentMousePos; }
    [[nodiscard]] inline Maths::Vector2 GetMouseDelta() const override { const Maths::Vector2 l_delta = m_currentMousePos - m_previousMousePos; const Maths::Vector2 l_result = l_delta; return l_result; }
    [[nodiscard]] inline Maths::Vector2 GetMouseScroll() override { const Maths::Vector2 l_returnVal = m_mouseScroll; m_mouseScroll = Maths::Vector2::Zero; return l_returnVal; }
    [[nodiscard]] inline unsigned int GetCurrentMods() const { return m_currentMods; }


    inline void ResetMouseDelta() override { m_previousMousePos = m_currentMousePos; }
    inline void SetCursorPosition(const double& a_xPos, const double& a_yPos) override { m_currentMousePos.x = static_cast<float>(a_xPos); m_currentMousePos.y = static_cast<float>(a_yPos); }
    inline void SetMouseScroll(const double& a_xAxis, const double& a_yAxis) override { m_mouseScroll.x = static_cast<float>(a_xAxis); m_mouseScroll.y = static_cast<float>(a_yAxis); }
    inline void ConfigureMouseInput(const CursorInputMode& a_cursorInputMode) override { glfwSetInputMode(m_window->GetGLFWWindow(), GLFW_CURSOR, CastGlfwInput(a_cursorInputMode)); }

    void CreateAction(const std::string& a_actionName) override;
    void AddBinding(const std::string& a_actionName, Key a_key, int a_mods) override;
    void UnbindAction(const std::string& a_actionName, Key a_key, int a_mods) override;

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

    inline void OnCursorPositionUpdate(const double& a_xPos, const double& a_yPos) { m_currentMousePos.x = static_cast<float>(a_xPos); m_currentMousePos.y = static_cast<float>(a_yPos); }
    inline void OnScrollUpdate(const double& a_xAxis, const double& a_yAxis) { m_mouseScroll.x = static_cast<float>(a_xAxis); m_mouseScroll.y = static_cast<float>(a_yAxis); }
    [[nodiscard]] inline bool IsKeyValid(const int a_key) const { return a_key >= 0 && a_key < static_cast<int>(m_keyPressed.size()); }
    [[nodiscard]] inline bool IsKeyValid(const Key a_key) const { const int l_keyIndex = static_cast<int>(a_key); return l_keyIndex >= 0 && l_keyIndex < static_cast<int>(m_keyPressed.size()); }

    inline static int ToIndex(Key a_ckey) { return static_cast<int>(a_ckey); }
    inline static int ToIndex(MouseButton a_mouseButton) { return static_cast<int>(a_mouseButton); }

    int m_currentMods { 0 };
    std::array<int, LUMINOUS_KEY_LAST> m_keyPressed {};
    std::array<Action, LUMINOUS_KEY_LAST> m_keyStatus {};
    std::array<int, LUMINOUS_MOUSE_BUTTON_LAST> m_mouseButtonPressed {};
    std::array<Action, LUMINOUS_MOUSE_BUTTON_LAST> m_mouseButtonStatus {};
    std::unordered_map<std::string, InputAction> m_actions {};
    Maths::Vector2 m_mouseScroll { Maths::Vector2::Zero };
    Maths::Vector2 m_currentMousePos { Maths::Vector2::Zero };
    Maths::Vector2 m_previousMousePos { Maths::Vector2::Zero };
    GLFWWindow* m_window { nullptr };
};
