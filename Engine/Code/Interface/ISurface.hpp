#pragma once

#include "Logger.hpp"

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
		DEBUG_LOG_ERROR("Vulkan Surface : Cast is Wrong!\n");
		return nullptr;
	}
};
