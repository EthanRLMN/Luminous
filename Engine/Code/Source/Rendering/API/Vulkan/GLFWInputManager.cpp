#include "Rendering/API/Vulkan/GLFWInputManager.hpp"
#include "Rendering/API/Vulkan/VulkanWindow.hpp"

#include "IWindow.hpp"

std::array<int, 400> GLFWInputManager::m_keyPressed{};
std::array<int, 400> GLFWInputManager::m_keyStatus{};

int GLFWInputManager::IsKeyDown(IWindow* a_window, const int a_key)
{
	return m_keyStatus[a_key] == GLFW_PRESS || m_keyStatus[a_key] == GLFW_REPEAT;
}

int GLFWInputManager::IsKeyUp(IWindow* a_window, const int a_key)
{
	return m_keyStatus[a_key] == GLFW_RELEASE;
}

int GLFWInputManager::IsKeyPressed(IWindow* a_window, int a_key)
{
	if (m_keyPressed[a_key] == 0)
	{
		if (m_keyStatus[10] == 1)
		{
			m_keyPressed[a_key] = 1;
			return m_keyStatus[a_key] == GLFW_PRESS;

			m_keyStatus[a_key] = 0;
		}
		return false;
	}
	return false;
}

void GLFWInputManager::KeyCallback(GLFWwindow* a_window, int a_key, int a_scancode, const int a_action, int a_mods)
{

	if (a_action == GLFW_RELEASE)
		m_keyPressed[a_key] = 0;

	m_keyStatus[a_key] = a_action;

}

int GLFWInputManager::IsMouseButtonUp(IWindow* a_window, int a_button)
{
	return false;
}

int GLFWInputManager::IsMouseButtonDown(IWindow* a_window, int a_button)
{
	return false;
}

int GLFWInputManager::IsMouseButtonPressed(IWindow* a_window, int a_button)
{
	return false;
}

void GLFWInputManager::Initialize(IWindow* a_window)
{
	std::cout << GLFW_REPEAT << '\n';
	std::cout << GLFW_RELEASE << '\n';
	glfwSetKeyCallback(a_window->CastVulkan()->GetGLFWWindow(), KeyCallback);

}
