#pragma once
#include "IInputManager.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "Exporter.hpp"
#include <vector>

class LUMINOUS_ENGINE_API VulkanInputManager : public IInputManager
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

    VulkanInputManager* CastVulkan() override { return this; }

private:
    inline static int m_keyStatus[400];
    inline static int m_keyPressed[400];
    //std::vector<int> m_keyStatus;
};