#pragma once

#include "Logger.hpp"

class VulkanRenderPass;
class ISwapChain;
class IDevice;

class IRenderPass
{
public:
	virtual ~IRenderPass() = default;

	virtual void Create(ISwapChain* a_swapChain, IDevice* a_device) = 0;
	virtual void Destroy(IDevice* _device) = 0;

	virtual VulkanRenderPass* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan RenderPass : Cast is Wrong!\n");
		return nullptr;
	}
};
