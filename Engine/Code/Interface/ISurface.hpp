#pragma once

#include <iostream>

class VulkanSurface;
class IInstance;
class IWindow;

class ISurface
{
public:
	virtual ~ISurface() = default;
	virtual void Create(IInstance* a_instance, IWindow* a_window) = 0;
	virtual void Destroy(IInstance* a_instance) = 0;

	virtual VulkanSurface* CastVulkan()
	{
		std::cout << "Vulkan Surface : Wrong cast\n";
		return nullptr;
	}
};
