#include "Rendering/API/Vulkan/VulkanInputManager.hpp"

int VulkanInputManager::IsKeyDown(IWindow* a_window, const int a_key)
{
	return m_keyStatus[a_key] == GLFW_PRESS || m_keyStatus[a_key] == GLFW_REPEAT;
}

int VulkanInputManager::IsKeyUp(IWindow* a_window, const int a_key)
{
	return m_keyStatus[a_key] == GLFW_RELEASE;
}

int VulkanInputManager::IsKeyPressed(IWindow* a_window, int a_key)
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

void VulkanInputManager::KeyCallback(GLFWwindow* a_window, const int a_key, int a_scancode, const int a_action, int a_mods)
{

	if (a_action == GLFW_RELEASE)
		m_keyPressed[a_key] = 0;

	m_keyStatus[a_key] = a_action;
	
}

int VulkanInputManager::IsMouseButtonUp(IWindow* a_window, int a_button)
{
	return m_mouseButtonStatus[a_button] == GLFW_RELEASE;
}

int VulkanInputManager::IsMouseButtonDown(IWindow* a_window, int a_button)
{
	return m_mouseButtonStatus[a_button] == GLFW_PRESS || m_mouseButtonStatus[a_button] == GLFW_REPEAT;
}

int VulkanInputManager::IsMouseButtonPressed(IWindow* a_window, int a_button)
{
	if (m_mouseButtonPressed[a_button] == 0)
	{
		if (m_mouseButtonStatus[a_button] == GLFW_PRESS)
		{
			m_mouseButtonPressed[a_button] = 1;
			return m_mouseButtonStatus[a_button] == GLFW_PRESS;
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}
}

void VulkanInputManager::MouseButtonCallback(GLFWwindow* a_window, int a_key, int a_action, int a_mods)
{

	if (a_action == GLFW_RELEASE)
	{
		m_mouseButtonPressed[a_key] = 0;
	}

	m_mouseButtonStatus[a_key] = a_action;

}

void VulkanInputManager::MouseScrollCallback(GLFWwindow* a_window, double a_xoffset, double a_yoffset)
{

	m_mouseScroll[0] = (float)a_xoffset;
	m_mouseScroll[1] = (float)a_yoffset;

}

void VulkanInputManager::SetMouseScroll(Vector2 a_vec)
{
}

Vector2 VulkanInputManager::GetCursorPosition(IWindow* a_window)
{
	double t_x, t_y;
	glfwGetCursorPos(a_window->CastVulkan()->GetGLFWWindow(), &t_x, &t_y);
	return Vector2((float)t_x, (float)t_y);
}

void VulkanInputManager::SetCursorPosition(IWindow* a_window, Vector2 a_pos)
{
	glfwSetCursorPos(a_window->CastVulkan()->GetGLFWWindow(), (double)a_pos.x, (double)a_pos.y);
}

void VulkanInputManager::Initialize(IWindow* a_window)
{
	std::cout << GLFW_REPEAT << '\n';
	std::cout << GLFW_RELEASE << '\n';
	glfwSetKeyCallback(a_window->CastVulkan()->GetGLFWWindow(), KeyCallback);
	glfwSetMouseButtonCallback(a_window->CastVulkan()->GetGLFWWindow(), MouseButtonCallback);
	glfwSetScrollCallback(a_window->CastVulkan()->GetGLFWWindow(), MouseScrollCallback);

}
