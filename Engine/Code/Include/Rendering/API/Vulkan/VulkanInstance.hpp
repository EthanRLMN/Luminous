#pragma once

#define GLFW_INCLUDE_VULKAN
#include <vector>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h> 

#include "IInstance.hpp"

class Window;

class VulkanInstance : public IInstance
{
public :
	~VulkanInstance() override = default;

	void Create(IWindow* a_window) override;
	void Destroy() override;

	[[nodiscard]] virtual VkInstance GetInstance() const { return m_instance; }

	VulkanInstance* CastVulkan() override { return this; }

private:
	void CreateInstance();
	void Debug();

	bool CheckValidationLayerSupport();
	bool CheckInstanceExtensionSupport(std::vector<const char*>* a_checkExtensions);

	VkInstance m_instance { VK_NULL_HANDLE };
	VkDebugUtilsMessengerEXT m_callback { VK_NULL_HANDLE };
};
