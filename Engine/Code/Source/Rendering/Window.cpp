#include "Rendering/Window.hpp"

void Window::Initialize(const std::string& a_name, const int a_width, const int a_height)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	if (glfwVulkanSupported())
		std::cout << "Vulkan Support Working!\n";

	m_Window = glfwCreateWindow(a_width, a_height, a_name.c_str(), nullptr, nullptr);

	if (m_Window)
	{
		std::cout << "Sucess win dows" << "\n";
	} else
	{
		std::cout << "Failed windows" << "\n";
	}
}

void Window::Update() const
{
	while (!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();
	}
}

void Window::InputManager(const GLFWkeyfun a_input) const
{
	glfwSetKeyCallback(m_Window, a_input);
}

void Window::Shutdown() const
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}
