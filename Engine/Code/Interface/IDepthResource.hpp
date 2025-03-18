#pragma once

#include "Logger.hpp"

class VulkanDepthResource;

class IDevice;
class ISwapChain;
class IRenderPass;

class IDepthResource
{
public:
	virtual ~IDepthResource() = default;

	virtual void Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass) = 0;
	virtual void Destroy() = 0;

	virtual VulkanDepthResource* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Depth Resource : Cast is Wrong!\n");
		return nullptr;
	}
};
