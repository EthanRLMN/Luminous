#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <vector>
#include "IInstance.hpp"

class Window;

class VulkanInstance final : public IInstance
{
public :
	~VulkanInstance() override = default;

	void Create(IWindow* a_window) override;
	void Destroy() override;

	[[nodiscard]] VkInstance GetInstance() const { return m_instance; }
	[[nodiscard]] VkDebugUtilsMessengerEXT GetDebugUtilsMessagerExt() const { return m_debugMessenger; }

	VulkanInstance* CastVulkan() override { return this; }

private:
	void CreateInstance();
	void Debug();

	bool CheckValidationLayerSupport();
	bool CheckInstanceExtensionSupport(const std::vector<const char*>* a_checkExtensions);

	VkInstance m_instance { VK_NULL_HANDLE };
	VkDebugUtilsMessengerEXT m_debugMessenger{ VK_NULL_HANDLE };
};
