#pragma once
#include <Logger.hpp>

class VulkanSynchronization;
class IDevice;

class ISynchronization
{
public:
	virtual ~ISynchronization() = default;

	virtual void Create(IDevice* a_device) = 0;
	virtual void Destroy() = 0;

	virtual VulkanSynchronization* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Synchronizaion : Cast is Wrong!\n");
		return nullptr;
	}
};
