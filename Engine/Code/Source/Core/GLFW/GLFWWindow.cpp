#include "Core/GLFW/GLFWWindow.hpp"

#include "Vector2.hpp"

GLFWwindow* GLFWWindow::Initialize(const std::string& a_name, const int& a_width, const int& a_height)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

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
    Initialize(a_name, 800, 600);
    SetSize(Maths::Vector2(static_cast<float>(m_vidMode->width), static_cast<float>(m_vidMode->height)));

    glfwSetWindowPos(m_window, 1, 35);
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
    DEBUG_LOG_INFO("GLFW Window : Destroy!\n");
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
    /*
    double currentTime = glfwGetTime();
    float deltaTime = static_cast<float>(currentTime - m_lastTime);
    m_lastTime = currentTime;
    return deltaTime;*/

    return 0.0f;
}
