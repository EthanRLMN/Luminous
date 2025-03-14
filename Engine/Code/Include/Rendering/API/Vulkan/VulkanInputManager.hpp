#pragma once
#include "IInputManager.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "Exporter.hpp"

class LUMINOUS_ENGINE_API VulkanInputManager final : public IInputManager
{
public:
    void Initialize(IWindow* a_window) override;

    int IsKeyDown(IWindow* a_window, int a_key) override;
    int IsKeyUp(IWindow* a_window, int a_key) override;
    int IsKeyPressed(IWindow* a_window, int a_key) override;
    static void KeyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);

    int IsMouseButtonDown(IWindow* a_window, int a_button) override;
    int IsMouseButtonUp(IWindow* a_window, int a_button) override;
    int IsMouseButtonPressed(IWindow* a_window, int a_button) override;
    static void MouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods);

    Vector2 GetCursorPosition(IWindow* a_window) override;
    void SetCursorPosition(IWindow* a_window, Vector2 a_pos) override;

    VulkanInputManager* CastVulkan() override { return this; }

private:
    inline static int m_keyPressed[400];
    inline static std::array<int, 400> m_keyStatus;

    inline static int m_mouseButtonStatus[16];
    inline static int m_mouseButtonPressed[16];

    //std::vector<int> m_keyStatus;
};