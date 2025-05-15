#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "IWindow.hpp"

class Vector2;


class GLFWWindow final : public IWindow
{
public:
    static constexpr int DefaultWidth = 1280;
    static constexpr int DefaultHeight = 720;

    GLFWwindow* Initialize(const std::string& a_name, int a_width, int a_height, bool a_useScreenSize) override;
    void Initialize(const std::string& a_name, bool a_useScreenSize) override;
    void Update() const override;
    void Destroy() const override;

    inline void PollEvents() const override { glfwPollEvents(); }
    inline void SetSize(const Maths::Vector2& a_size) override { glfwSetWindowSize(m_window, static_cast<int>(a_size.x), static_cast<int>(a_size.y)); }
    inline void SetOpacity(const float& a_alpha) override { glfwSetWindowOpacity(m_window, a_alpha); }
    inline void SetTitle(const std::string& a_name) override { glfwSetWindowTitle(m_window, a_name.c_str()); }
    inline void ProcessEvents() override { glfwWaitEvents(); }
    inline void SetFrameBufferResized(const bool a_isResized) { m_isFrameBufferResized = a_isResized; }

    [[Nodiscard]] inline bool IsFrameBufferResized() const override { return m_isFrameBufferResized; }
    [[nodiscard]] inline bool ShouldClose() const override { return glfwWindowShouldClose(m_window); }
    [[nodiscard]] inline float GetOpacity() const override { return glfwGetWindowOpacity(m_window); }
    [[nodiscard]] inline std::string GetTitle() const override { return glfwGetWindowTitle(m_window); }
    [[nodiscard]] Maths::Vector2 GetSize() const override;

    void GetFrameBufferSize(int* a_width, int* a_height) override { glfwGetFramebufferSize(m_window, a_width, a_height); }
    [[nodiscard]] const GLFWvidmode& GetMonitorInformation() const { return *m_vidMode; }
    [[nodiscard]] GLFWwindow* GetGLFWWindow() const { return m_window; }

    GLFWWindow* CastGLFW() override { return this; }
    

private:
    static void FramebufferResizeCallback(GLFWwindow* a_window, int a_width, int a_height);
    void RetrieveMonitorInformation();

    bool m_isFrameBufferResized { false };
    GLFWwindow* m_window { nullptr };
    GLFWmonitor* m_monitor { nullptr };
    const GLFWvidmode* m_vidMode { nullptr };
};
