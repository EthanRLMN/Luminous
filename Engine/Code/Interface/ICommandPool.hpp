#pragma once

#include "Logger.hpp"

class VulkanCommandPool;
class IDevice;
class ISurface;

class ICommandPool
{
public:
	virtual ~ICommandPool() = default;

	virtual void Create(IDevice* a_device, ISurface* a_surface) = 0;
	virtual void Destroy(IDevice* a_device) = 0;


	virtual VulkanCommandPool* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan CommandPool : Cast is Wrong!\n");
		return nullptr;
	}

};
