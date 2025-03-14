#include "Rendering/API/Vulkan/VulkanWindow.hpp"

void VulkanWindow::Initialize(const std::string& a_name, const int a_width, const int a_height)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    if (glfwVulkanSupported())
        std::cout << "Vulkan Support Working!\n";

    m_window = glfwCreateWindow(a_width, a_height, a_name.c_str(), nullptr, nullptr);

    if (m_window)
        std::cout << "Window Created!\n";
    else
        std::cout << "Failed windows\n";
}

void VulkanWindow::Update() const
{
    while (!ShouldClose())
    {
        PollEvents();
    }
    Destroy();
}

void VulkanWindow::PollEvents() const
{
    glfwPollEvents();
}

bool VulkanWindow::ShouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void VulkanWindow::Destroy() const
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

Vector2 VulkanWindow::GetSize()
{
    int t_x, t_y;
    glfwGetWindowSize(m_window, &t_x, &t_y);
    return Vector2((float)t_x, (float)t_y);
}

void VulkanWindow::SetSize(const Vector2 a_size)
{
    glfwSetWindowSize(m_window, (int)a_size.x, (int)a_size.y);
}

float VulkanWindow::GetOpacity()
{
    return glfwGetWindowOpacity(m_window);
}

void VulkanWindow::SetOpacity(const float a_alpha)
{
    glfwSetWindowOpacity(m_window, a_alpha);
}

const std::string VulkanWindow::GetTitle()
{
    std::string t_str = glfwGetWindowTitle(m_window);
    return t_str;
}

void VulkanWindow::SetTitle(const std::string& a_name)
{
    glfwSetWindowTitle(m_window,a_name.c_str());
}

Vector2 VulkanWindow::GetCursorPosition()
{
    double t_x, t_y;
    glfwGetCursorPos(m_window, &t_x, &t_y);
    return Vector2((float)t_x, (float)t_y);
}

