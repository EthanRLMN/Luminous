#pragma once
#include "IWindow.hpp"

#define GLFW_INCLUDE_VULKAN
#include <Vector2.hpp>
#include <GLFW/glfw3.h>

class VulkanWindow final : public IWindow
{
public:
    GLFWwindow* Initialize(const std::string& a_name, int a_width, int a_height) override;
    void Update() const override;
    void PollEvents() const override;
    [[nodiscard]] bool ShouldClose() const override;
    void Destroy() const override;

    Maths::Vector2 GetSize() override;
    void SetSize(Maths::Vector2 a_size) override;
    float GetOpacity() override;
    void SetOpacity(float a_alpha) override;
    const std::string GetTitle() override;
    void SetTitle(const std::string& a_name) override;

    VulkanWindow* CastVulkan() override { return this; }

    GLFWwindow* GetGLFWwindow() const { return m_window; }
    VkInstance GetVulkanInstance() const { return m_instance; }

private:
    GLFWwindow* m_window = nullptr;
    VkInstance m_instance = nullptr;

    void CreateVulkanInstance();
};
