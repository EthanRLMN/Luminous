#pragma once

#include <vulkan/vulkan.h>

#include "IDevice.hpp"

#include "Struct/VulkanUtilities.hpp"

#include "Utils/QueueFamilyIndiceUtils.hpp"

class VulkanDevice final : public IDevice
{
public:
	~VulkanDevice() override = default;
	void Create(IInstance* a_instance, IWindow* a_window, ISurface* a_surface) override;
	void Destroy() override;
	
	[[nodiscard]] VkDevice GetDevice() const { return m_device; }
	[[nodiscard]] VkPhysicalDevice GetPhysicalDevice() const { return m_physicalDevice; }
	[[nodiscard]] VkQueue GetGraphicsQueue() const { return m_graphicsQueue; }
	[[nodiscard]] VkQueue GetPresentationQueue() const { return m_presentationQueue; }


	VulkanDevice* CastVulkan() override { return this; }
	
	void CreateLogicalDevice(VkSurfaceKHR a_surface,VkInstance a_instance);
	void GetPhysicalDevice(VkInstance a_instance, VkSurfaceKHR a_surface);
	bool CheckDeviceSuitable(VkPhysicalDevice a_device, VkSurfaceKHR a_surface);
	SwapChainDetails GetSwapChainDetails(VkPhysicalDevice a_device, VkSurfaceKHR a_surface);
	bool CheckDeviceExtensionSupport(VkPhysicalDevice a_device);
	QueueFamilyIndices GetQueueFamilies(VkPhysicalDevice a_device, VkSurfaceKHR a_surface);


private :
	VkDevice m_device{ VK_NULL_HANDLE };
	VkPhysicalDevice m_physicalDevice{ VK_NULL_HANDLE };
	VkQueue m_graphicsQueue{ VK_NULL_HANDLE };
	VkQueue m_presentationQueue{ VK_NULL_HANDLE };
};
