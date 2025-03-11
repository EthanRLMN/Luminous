#pragma once
#include "IWindow.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class VulkanWindow : public IWindow
{
public:
    void Initialize(const std::string& a_name, int a_width, int a_height) override;
    void Update() const override;
    void Destroy() const override;

    VulkanWindow* CastVulkan() override { return this; }

    GLFWwindow* GetGLFWWindow() const { return m_window; }

private:
    GLFWwindow* m_window = nullptr;
};
