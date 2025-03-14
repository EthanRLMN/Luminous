#include "Rendering/API/Vulkan/VulkanInputManager.hpp"

int VulkanInputManager::IsKeyDown(IWindow* a_window, int a_key)
{
	return glfwGetKey(a_window->CastVulkan()->GetGLFWWindow(), a_key) == GLFW_PRESS;
}

int VulkanInputManager::IsKeyUp(IWindow* a_window, int a_key)
{
	return glfwGetKey(a_window->CastVulkan()->GetGLFWWindow(), a_key) == GLFW_RELEASE;
}
