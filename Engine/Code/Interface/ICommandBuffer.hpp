#pragma once
#include "Logger.hpp"

class VulkanCommandBuffer;
class IDevice;
class ISwapChain;
class ICommandPool;


class ICommandBuffer
{
public:
	virtual ~ICommandBuffer() = default;

	virtual void Create(IDevice* a_device, ISwapChain* a_swapChain, ICommandPool* a_commandPool) = 0;
	virtual void Destroy() = 0;

	virtual VulkanCommandBuffer* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Pipeline : Cast is Wrong!\n");
		return nullptr;
	}
};