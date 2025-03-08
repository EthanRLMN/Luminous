#include "../../Code/Include/Rendering/Window.h"


void Window::Initialize(const std::string name, const int width, const int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	m_Window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

	if (m_Window) {
		std::cout << "Sucess windows" << std::endl;
	}
	else {
		std::cout << "Failed windows" << std::endl;
	}

}

void Window::Update()
{
	while (!glfwWindowShouldClose(m_Window)) {
		glfwPollEvents();
	}
}

void Window::InputManager(GLFWkeyfun _input)
{
	glfwSetKeyCallback(m_Window, _input);
}

void Window::Shutdown()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}
