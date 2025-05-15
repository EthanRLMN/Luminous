#include "Core/GLFW/GLFWWindow.hpp"

#include "Vector2.hpp"

GLFWwindow* GLFWWindow::Initialize(const std::string& a_name, const int a_width, const int a_height, const bool a_useScreenSize)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

    if (glfwVulkanSupported())
        DEBUG_LOG_INFO("Vulkan Window : GLFW Vulkan Support enabled!\n");

    RetrieveMonitorInformation();

    if (!a_useScreenSize)
        m_window = glfwCreateWindow(a_width, a_height, a_name.c_str(), nullptr, nullptr);
    else
        m_window = glfwCreateWindow(m_vidMode->width, m_vidMode->height, a_name.c_str(), nullptr, nullptr);

    glfwSetFramebufferSizeCallback(m_window, FramebufferResizeCallback);

    if (m_window)
    {
        DEBUG_LOG_INFO("Vulkan Window : Creation successful!\n");
        return m_window;
    }

    DEBUG_LOG_ERROR("Vulkan Window : Creation failed!\n");
    return nullptr;
}

void GLFWWindow::Initialize(const std::string& a_name, const bool a_useScreenSize)
{
    Initialize(a_name, DefaultWidth, DefaultHeight, a_useScreenSize);
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


void GLFWWindow::FramebufferResizeCallback(GLFWwindow* a_window, int a_width, int a_height)
{
    static_cast<void>(a_width); static_cast<void>(a_height);

    GLFWWindow* l_window = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(a_window));
    l_window->m_isFrameBufferResized = true;
}


void GLFWWindow::RetrieveMonitorInformation()
{
    m_monitor = glfwGetPrimaryMonitor();
    m_vidMode = glfwGetVideoMode(m_monitor);
}
