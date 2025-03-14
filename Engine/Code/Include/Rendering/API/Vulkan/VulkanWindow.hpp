#pragma once
#include "IWindow.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class VulkanWindow : public IWindow
{
public:
    void Initialize(const std::string& a_name, int a_width, int a_height) override;
    void Update() const override;
    void PollEvents() const override;
    bool ShouldClose() const  override;
    void Destroy() const override;

    Vector2 GetSize() override;
    void SetSize(const Vector2 a_size) override;
    float GetOpacity() override;
    void SetOpacity(const float a_alpha) override;
    const std::string GetTitle() override;
    void SetTitle(const std::string& a_name) override;
    Vector2 GetCursorPosition() override;

    VulkanWindow* CastVulkan() override { return this; }

    GLFWwindow* GetGLFWWindow() const { return m_window; }

private:
    GLFWwindow* m_window = nullptr;
};
