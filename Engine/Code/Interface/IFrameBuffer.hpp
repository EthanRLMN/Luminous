#pragma once

#include "Logger.hpp"

class VulkanFrameBuffer;
class IDevice;
class ISwapChain;
class IRenderPass;
class IDepthResource;
class IMultiSampling;

class IFrameBuffer {
public:
	virtual ~IFrameBuffer() = default;

	virtual void Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass, IDepthResource* a_depthRessource, IMultiSampling* a_multiSampling) = 0;
	virtual void Destroy(IDevice* a_device) = 0;

	virtual VulkanFrameBuffer* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Frame Buffer : Cast is Wrong!\n");
		return nullptr;
	}
};