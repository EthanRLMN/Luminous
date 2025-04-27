#include "Core/GLFW/GLFWWindow.hpp"

#include "Vector2.hpp"

GLFWwindow* GLFWWindow::Initialize(const std::string& a_name, const int& a_width, const int& a_height)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

    if (glfwVulkanSupported())
        DEBUG_LOG_INFO("Vulkan Window : GLFW Vulkan Support enabled!\n");

    RetrieveMonitorInformation();
    m_window = glfwCreateWindow(a_width, a_height, a_name.c_str(), nullptr, nullptr);
    if (m_window)
    {
        DEBUG_LOG_INFO("Vulkan Window : Creation successful!\n");
        return m_window;
    }

    DEBUG_LOG_ERROR("Vulkan Window : Creation failed!\n");
    return nullptr;
}

void GLFWWindow::Initialize(const std::string& a_name)
{
    Initialize(a_name, DefaultWidth, DefaultHeight);
}


void GLFWWindow::Update() const
{
    glfwSwapBuffers(m_window);
    PollEvents();
}


void GLFWWindow::Destroy() const
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
    DEBUG_LOG_INFO("GLFW Window : Window destroyed!\n");
}


Maths::Vector2 GLFWWindow::GetSize() const
{
    int t_x, t_y;
    glfwGetWindowSize(m_window, &t_x, &t_y);
    return Maths::Vector2{ static_cast<float>(t_x), static_cast<float>(t_y) };
}


void GLFWWindow::RetrieveMonitorInformation()
{
    m_monitor = glfwGetPrimaryMonitor();
    m_vidMode = glfwGetVideoMode(m_monitor);
}

float GLFWWindow::GetDeltaTime()
{
    const double l_currentTime = glfwGetTime();
    const float l_deltaTime = static_cast<float>(l_currentTime - m_lastTime);
    m_lastTime = l_currentTime;
    return l_deltaTime;
}
