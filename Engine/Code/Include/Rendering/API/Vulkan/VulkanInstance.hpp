#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "IInstance.hpp"

class Window;

class VulkanInstance : public IInstance
{
public :
	~VulkanInstance() override = default;

	void Create(IWindow* a_window) override;
	void Destroy() override;

	[[nodiscard]] VkInstance GetInstance() const { return m_instance; }

	VulkanInstance* CastVulkan() override { return this; }

private:
	void VkCreateInstance();
	void VkDebugCallback();

	VkInstance m_instance = VK_NULL_HANDLE;
	VkDebugReportCallbackEXT m_callback = VK_NULL_HANDLE;
};

