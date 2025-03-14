#include "Rendering/API/Vulkan/VulkanInputManager.hpp"

int VulkanInputManager::IsKeyDown(IWindow* a_window, int a_key)
{
	return m_keyStatus[a_key] == GLFW_PRESS;
}

int VulkanInputManager::IsKeyUp(IWindow* a_window, int a_key)
{
	return m_keyStatus[a_key] == GLFW_RELEASE;
	//return glfwGetKey(a_window->CastVulkan()->GetGLFWWindow(), a_key) == GLFW_RELEASE;
}

int VulkanInputManager::IsKeyPressed(IWindow* a_window, int a_key)
{
	return 0;
	//return glfwGetKey(a_window->CastVulkan()->GetGLFWWindow(), a_key) == GLFW_RELEASE;
}

void VulkanInputManager::KeyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods)
{
	m_keyStatus[a_key] = a_action;
}

void VulkanInputManager::Initialize(IWindow* a_window)
{
	glfwSetKeyCallback(a_window->CastVulkan()->GetGLFWWindow(), KeyCallback);

}
