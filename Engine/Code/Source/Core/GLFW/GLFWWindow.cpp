#include "Core/GLFW/GLFWWindow.hpp"

void GLFWWindow::Initialize(const std::string& a_name, const int a_width, const int a_height)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    if (glfwVulkanSupported())
        DEBUG_LOG_INFO("Vulkan Window : GLFW Vulkan Support enabled!\n");

    m_window = glfwCreateWindow(a_width, a_height, a_name.c_str(), nullptr, nullptr);

    if (m_window)
        DEBUG_LOG_INFO("Vulkan Window : Creation successful!\n");
    else
        DEBUG_LOG_ERROR("Vulkan Window : Creation failed!\n");
}

void GLFWWindow::Update() const
{
    while (!ShouldClose())
    {
        PollEvents();
    }

    Destroy();
}

void GLFWWindow::PollEvents() const
{
    glfwPollEvents();
}

bool GLFWWindow::ShouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void GLFWWindow::Destroy() const
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
    DEBUG_LOG_INFO("GLFW Window : Destroy!\n");
}

Maths::Vector2 GLFWWindow::GetSize()
{
    int t_x, t_y;
    glfwGetWindowSize(m_window, &t_x, &t_y);
    return Maths::Vector2{static_cast<float>(t_x), static_cast<float>(t_y)};
}

void GLFWWindow::SetSize(const Maths::Vector2 a_size)
{
    glfwSetWindowSize(m_window, static_cast<int>(a_size.x), static_cast<int>(a_size.y));
}

float GLFWWindow::GetOpacity()
{
    return glfwGetWindowOpacity(m_window);
}

void GLFWWindow::SetOpacity(const float a_alpha)
{
    glfwSetWindowOpacity(m_window, a_alpha);
}

std::string GLFWWindow::GetTitle() const
{
    std::string t_str = glfwGetWindowTitle(m_window);
    return t_str;
}

void GLFWWindow::SetTitle(const std::string& a_name)
{
    glfwSetWindowTitle(m_window,a_name.c_str());
}