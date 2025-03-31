#pragma once

#include "IWindow.hpp"

#include <Vector2.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class GLFWWindow final : public IWindow
{
public:
    void Initialize(const std::string& a_name, int a_width, int a_height) override;
    void Update() const override;
    void PollEvents() const override;
    [[nodiscard]] bool ShouldClose() const override;
    void Destroy() const override;

    Maths::Vector2 GetSize() override;
    void SetSize(Maths::Vector2 a_size) override;
    float GetOpacity() override;
    void SetOpacity(float a_alpha) override;
    [[nodiscard]] std::string GetTitle() const override;
    void SetTitle(const std::string& a_name) override;

    GLFWWindow* CastGLFW() override { return this; }

    [[nodiscard]] GLFWwindow* GetGLFWWindow() const { return m_window; }


private:
    GLFWwindow* m_window = nullptr;
};
