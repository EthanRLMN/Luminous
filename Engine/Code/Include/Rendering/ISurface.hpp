#pragma once

#include <iostream>

class VulkanSurface;
class IInstance;
class Window;

class ISurface
{
public:
	virtual ~ISurface() = default;
	virtual void Create(IInstance* a_instance, Window* a_window) = 0;
	virtual void Destroy(IInstance* a_instance) = 0;

	virtual VulkanSurface* CastVulkan()
	{
		std::cout << "Wrong cast" << std::endl;
		return nullptr;
	}
};
