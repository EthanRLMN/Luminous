#pragma once

#include "Logger.hpp"

class VulkanModel;


class IModel
{
public:
	virtual ~IModel() = default;
	virtual void Create() = 0;
	virtual void Destroy() = 0;

	virtual VulkanModel* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Surface : Cast is Wrong!\n");
		return nullptr;
	}
};