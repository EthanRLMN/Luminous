#pragma once

#include <iostream>

class VulkanSurface;
class IInstance;
class EWindow;

class ISurface
{
public:
	virtual ~ISurface() = default;
	virtual void Create(IInstance* a_instance, EWindow* a_window) = 0;
	virtual void Destroy(IInstance* a_instance) = 0;

	virtual VulkanSurface* CastVulkan()
	{
		std::cout << "Vulkan Surface : Wrong cast\n";
		return nullptr;
	}
};
