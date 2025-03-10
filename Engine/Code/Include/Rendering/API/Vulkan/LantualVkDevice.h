#pragma once
#include "LantualVkDevice.h"
#include "../../LantualDevice.h"
#include "LantualVKInstance.h"
#include "LantualVkSurface.h"
#include <vulkan/vulkan.h>
#include "Utilities.h"
#include "LantualVkValidation.h"
#include "set"

class LantualVkDevice : public LantualDevice
{
public:
	LantualVkDevice() = default;
	~LantualVkDevice() = default;


	void Create(LantualInstance* _instance, Window* _window, LantualSurface* _surface) override;
	void Destroy() override;
	
	virtual VkDevice GetDevice() const 
	{
		return device;
	}

	LantualDevice* CastVulkan() override { return this; }
	
	void CreateLogicalDevice(VkSurfaceKHR _surface,VkInstance _instance);
	void GetPhysicalDevice(VkInstance _instance, VkSurfaceKHR _surface);

	bool checkDeviceSuitable(VkPhysicalDevice _device, VkSurfaceKHR _surface);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	QueueFamilyIndices getQueueFamilies(VkPhysicalDevice _device, VkSurfaceKHR _surface);

	SwapChainDetails getSwapChainDetails(VkPhysicalDevice _device, VkSurfaceKHR _surface);

	VkPhysicalDevice GetPhysicalDevice() const;
	VkQueue GetGraphicsQueue() const;
private :
	VkDevice device = VK_NULL_HANDLE;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkQueue graphicsQueue = VK_NULL_HANDLE;
	VkQueue presentationQueue = VK_NULL_HANDLE;
};
