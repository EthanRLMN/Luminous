#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "IWindow.hpp"

class Vector2;


class GLFWWindow final : public IWindow
{
public:
    GLFWwindow* Initialize(const std::string& a_name, const int& a_width, const int& a_height) override;
    void Initialize(const std::string& a_name) override;

    void Update() const override;
    inline void PollEvents() const override { glfwPollEvents(); }
    void Destroy() const override;

    inline void SetSize(const Maths::Vector2& a_size) override { glfwSetWindowSize(m_window, static_cast<int>(a_size.x), static_cast<int>(a_size.y)); }
    inline void SetOpacity(const float& a_alpha) override { glfwSetWindowOpacity(m_window, a_alpha); }
    inline void SetTitle(const std::string& a_name) override { glfwSetWindowTitle(m_window, a_name.c_str()); }
    inline void ProcessEvents() override { glfwWaitEvents(); }

    [[nodiscard]] inline bool ShouldClose() const override { return glfwWindowShouldClose(m_window); }
    [[nodiscard]] inline float GetOpacity() const override { return glfwGetWindowOpacity(m_window); }
    [[nodiscard]] inline std::string GetTitle() const override { return glfwGetWindowTitle(m_window); }

    [[nodiscard]] Maths::Vector2 GetSize() const override;
    [[nodiscard]] static float GetDeltaTime();

    void GetFrameBufferSize(int* a_width, int* a_height) override { glfwGetFramebufferSize(m_window, a_width, a_height); }
    [[nodiscard]] const GLFWvidmode& GetMonitorInformation() const { return *m_vidMode; }
    [[nodiscard]] GLFWwindow* GetGLFWWindow() const { return m_window; }

    GLFWWindow* CastGLFW() override { return this; }
    

private:
    void RetrieveMonitorInformation();

    GLFWwindow* m_window { nullptr };
    GLFWmonitor* m_monitor { nullptr };
    const GLFWvidmode* m_vidMode { nullptr };

    float m_lastTime { 0.0f };
};
