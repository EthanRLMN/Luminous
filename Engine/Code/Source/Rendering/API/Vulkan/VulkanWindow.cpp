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
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();

    }
}

void VulkanWindow::Destroy() const
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
