#pragma once

#include <vulkan/vulkan.h>

#include "IDevice.hpp"
#include "Utilities.hpp"
#include "VulkanDevice.hpp"

class VulkanDevice : public IDevice
{
public:
	~VulkanDevice() override = default;

	void Create(IInstance* a_instance, IWindow* a_window, ISurface* a_surface) override;

	void Destroy() override;
	
	[[nodiscard]] virtual VkDevice GetDevice() const { return m_device; }

	VulkanDevice* CastVulkan() override { return this; }
	
	void CreateLogicalDevice(VkSurfaceKHR a_surface,VkInstance a_instance);
	void GetPhysicalDevice(VkInstance a_instance, VkSurfaceKHR a_surface);

	static bool CheckDeviceSuitable(VkPhysicalDevice _device, VkSurfaceKHR _surface);
	static bool CheckDeviceExtensionSupport(VkPhysicalDevice a_device);

	static QueueFamilyIndices GetQueueFamilies(VkPhysicalDevice a_device, VkSurfaceKHR a_surface);

	static SwapChainDetails GetSwapChainDetails(VkPhysicalDevice _device, VkSurfaceKHR _surface);

	[[nodiscard]] VkPhysicalDevice GetPhysicalDevice() const;
	[[nodiscard]] VkQueue GetGraphicsQueue() const;

private :
	VkDevice m_device = VK_NULL_HANDLE;
	VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
	VkQueue m_graphicsQueue = VK_NULL_HANDLE;
	VkQueue m_presentationQueue = VK_NULL_HANDLE;
};
