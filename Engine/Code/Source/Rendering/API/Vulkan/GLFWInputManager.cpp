#include "Rendering/API/Vulkan/GLFWInputManager.hpp"

#include "IWindow.hpp"
#include "Rendering/API/Vulkan/VulkanWindow.hpp"

std::array<int, 400> GLFWInputManager::m_keyPressed{};
std::array<int, 400> GLFWInputManager::m_keyStatus{};

std::array<int, 17> GLFWInputManager::m_mouseButtonStatus{};
std::array<int, 17> GLFWInputManager::m_mouseButtonPressed{};

std::array<int, 2> GLFWInputManager::m_mouseScroll{};

int GLFWInputManager::IsKeyDown(IWindow* a_window, const int a_key)
{
	return m_keyStatus[a_key] == GLFW_PRESS || m_keyStatus[a_key] == GLFW_REPEAT;
}

int GLFWInputManager::IsKeyUp(IWindow* a_window, const int a_key)
{
	return m_keyStatus[a_key] == GLFW_RELEASE;
}

int GLFWInputManager::IsKeyPressed(IWindow* a_window, const int a_key)
{
	if (m_keyPressed[a_key] == 0)
	{
		if (m_keyStatus[a_key] == GLFW_PRESS)
		{
			m_keyPressed[a_key] = 1;
			return m_keyStatus[a_key] == GLFW_PRESS;
		}
		return false;
	}
	return false;
}

void GLFWInputManager::KeyCallback(GLFWwindow* a_window, const int a_key, int a_scancode, const int a_action, int a_mods)
{

	if (a_action == GLFW_RELEASE)
		m_keyPressed[a_key] = 0;

	m_keyStatus[a_key] = a_action;

}

int GLFWInputManager::IsMouseButtonUp(IWindow* a_window, const int a_button)
{
	return m_mouseButtonStatus[a_button] == GLFW_RELEASE;
}

int GLFWInputManager::IsMouseButtonDown(IWindow* a_window, const int a_button)
{
	return m_mouseButtonStatus[a_button] == GLFW_PRESS || m_mouseButtonStatus[a_button] == GLFW_REPEAT;
}

int GLFWInputManager::IsMouseButtonPressed(IWindow* a_window, const int a_button)
{
	if (m_mouseButtonPressed[a_button] == 0)
	{
		if (m_mouseButtonStatus[a_button] == GLFW_PRESS)
		{
			m_mouseButtonPressed[a_button] = 1;
			return m_mouseButtonStatus[a_button] == GLFW_PRESS;
		}
		return false;
	}
	return false;
}

void GLFWInputManager::MouseButtonCallback(GLFWwindow* a_window, const int a_button, const int a_action, int a_mods)
{

	if (a_action == GLFW_RELEASE)
		m_mouseButtonPressed[a_button] = 0;

	m_mouseButtonStatus[a_button] = a_action;

}

void GLFWInputManager::MouseScrollCallback(GLFWwindow* a_window, const double a_xOffset, const double a_yOffset)
{
	m_mouseScroll[0] = static_cast<int>(a_xOffset);
	m_mouseScroll[1] = static_cast<int>(a_yOffset);
}

void GLFWInputManager::SetMouseScroll(Maths::Vector2 a_vec)
{
}

Maths::Vector2 GLFWInputManager::GetCursorPosition(IWindow* a_window)
{
	double t_x, t_y;
	glfwGetCursorPos(m_window, &t_x, &t_y);
	return Maths::Vector2(static_cast<float>(t_x), static_cast<float>(t_y));
}

void GLFWInputManager::SetCursorPosition(IWindow* a_window, const Maths::Vector2 a_pos)
{
	glfwSetCursorPos(m_window, a_pos.x, a_pos.y);
}

Maths::Vector2 GLFWInputManager::GetMouseScroll()
{
	return Maths::Vector2(static_cast<float>(m_mouseScroll[0]),static_cast<float>(m_mouseScroll[1]));
}

void GLFWInputManager::Initialize(IWindow* a_window)
{
	std::cout << GLFW_REPEAT << '\n';
	std::cout << GLFW_RELEASE << '\n';
	m_window = a_window->CastVulkan()->GetGLFWWindow();

	glfwSetKeyCallback(m_window, KeyCallback);
	glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
	glfwSetScrollCallback(m_window, MouseScrollCallback);
}

void GLFWInputManager::Destroy(IWindow* a_window)
{
	glfwDestroyWindow(a_window->CastVulkan()->GetGLFWWindow());
	glfwTerminate();
}

void GLFWInputManager::Update(IWindow* a_window)
{
	m_mouseScroll[0] = 0;
	m_mouseScroll[1] = 0;
}
