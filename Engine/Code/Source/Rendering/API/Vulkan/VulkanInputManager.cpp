#include "Rendering/API/Vulkan/VulkanInputManager.hpp"

int VulkanInputManager::IsKeyDown(IWindow* a_window, int a_key)
{
	return m_keyStatus[a_key] == GLFW_PRESS || m_keyStatus[a_key] == GLFW_REPEAT;
}

int VulkanInputManager::IsKeyUp(IWindow* a_window, int a_key)
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
		else 
		{ 
			return false; 
		}
		
	}else 
	{
		return false;
	}

}

void VulkanInputManager::KeyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods)
{

	if (a_action == GLFW_RELEASE)
	{
		m_keyPressed[a_key] = 0;
	}

	m_keyStatus[a_key] = a_action;
	
}

int VulkanInputManager::IsMouseButtonUp(IWindow* a_window, int a_key)
{
	return false;
}

int VulkanInputManager::IsMouseButtonDown(IWindow* a_window, int a_key)
{
	return false;
}

int VulkanInputManager::IsMouseButtonPressed(IWindow* a_window, int a_key)
{
	return false;
}

void VulkanInputManager::Initialize(IWindow* a_window)
{
	std::cout << GLFW_REPEAT << '\n';
	std::cout << GLFW_RELEASE << '\n';
	glfwSetKeyCallback(a_window->CastVulkan()->GetGLFWWindow(), KeyCallback);

}
