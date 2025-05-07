#pragma once

#include <vector>
#include <vulkan/vulkan_core.h>

#include "IInstance.hpp"

class Window;

class VulkanInstance final : public IInstance
{
public :
	~VulkanInstance() override = default;

	void Create() override;
	void Destroy() override;

	[[nodiscard]] VkInstance GetInstance() const { return m_instance; }
	[[nodiscard]] VkDebugUtilsMessengerEXT GetDebugUtilsMessengerExt() const { return m_debugMessenger; }

	VulkanInstance* CastVulkan() override { return this; }

private:
	void CreateInstance();
	void Debug();
	void SetupValidationLayers(VkInstanceCreateInfo& a_createInfo);

	void SetupApplicationInfo(VkApplicationInfo& a_applicationInfo);
	void SetupDebugCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& a_createInfo);

	bool CheckValidationLayerSupport();
	bool CheckInstanceExtensionSupport(const std::vector<const char*>* a_checkExtensions);

	VkInstance m_instance { nullptr };
	VkDebugUtilsMessengerEXT m_debugMessenger{ nullptr };
};
