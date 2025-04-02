#pragma once

#include "Logger.hpp"

class VulkanMesh;

class IMesh
{
public:
	virtual ~IMesh() = default;
	virtual void Create() = 0;
	virtual void Destroy() = 0;

	virtual VulkanMesh* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Model : Cast is Wrong!\n");
		return nullptr;
	}
};