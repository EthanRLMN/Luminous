#pragma once
#include <iostream>


class VulkanCommandPool;
class IDevice;
class ISurface;


class ICommandPool
{
public:
	virtual ~ICommandPool() = default;

	virtual void Create(IDevice* a_device, ISurface* a_surface) = 0;
	virtual void Destroy() = 0;


	virtual VulkanCommandPool* CastVulkan()
	{
		std::cout << "Vulkan Device : Wrong cast\n";
		return nullptr;
	}

};
