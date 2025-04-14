#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "IWindow.hpp"

#include "Vector2.hpp"


class GLFWWindow final : public IWindow
{
public:
    GLFWwindow* Initialize(const std::string& a_name, const int& a_width, const int& a_height) override;
    void Update() const override;
    void PollEvents() const override;
    [[nodiscard]] bool ShouldClose() const override;
    void Destroy() const override;

    Maths::Vector2 GetSize() const override;
    void SetSize(const Maths::Vector2& a_size) override;
    float GetOpacity() const override;
    void SetOpacity(const float& a_alpha) override;
    [[nodiscard]] std::string GetTitle() const override;
    void SetTitle(const std::string& a_name) override;
    [[nodiscard]] float GetDeltaTime();

    GLFWWindow* CastGLFW() override { return this; }

    [[nodiscard]] GLFWwindow* GetGLFWWindow() const { return m_window; }


private:
    GLFWwindow* m_window = nullptr;
    float m_lastTime = 0.0f;
};
