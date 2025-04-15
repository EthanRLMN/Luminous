#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "IWindow.hpp"

#include "Vector2.hpp"


class GLFWWindow final : public IWindow
{
public:
    GLFWwindow* Initialize(const std::string& a_name, const bool& a_fullscreen, const int& a_width = 800, const int& a_height = 600) override;
    void Update() const override;
    void PollEvents() const override;
    void Destroy() const override;
    void SetSize(const Maths::Vector2& a_size) override;
    void SetOpacity(const float& a_alpha) override;
    void SetTitle(const std::string& a_name) override;
    void ProcessEvents() override;

    [[nodiscard]] bool ShouldClose() const override;
    [[nodiscard]] Maths::Vector2 GetSize() const override;
    [[nodiscard]] float GetOpacity() const override;
    [[nodiscard]] std::string GetTitle() const override;
    [[nodiscard]] GLFWvidmode GetMonitorInformation() const { return m_vidMode; };

    GLFWWindow* CastGLFW() override { return this; }
    [[nodiscard]] GLFWwindow* GetGLFWWindow() const { return m_window; }

    void GetFrameBufferSize(int* a_width, int* a_height) override;

private:
    void GetMonitorInformation();

    GLFWmonitor* m_monitor { nullptr };
    GLFWwindow* m_window { nullptr };
    GLFWvidmode m_vidMode{};
};
