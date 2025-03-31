#pragma once

#include "Logger.hpp"

class VulkanTexture;

class IDevice;
class ISwapChain;
class IDepthResource;
class ICommandPool;

class ITexture {

public:
	virtual ~ITexture() = default;

	virtual void Create(IDevice* a_device, ISwapChain* a_swapChain, IDepthResource* a_depthResource, ICommandPool* a_commandPool) = 0;
	virtual void Destroy(IDevice* a_device) = 0;

	virtual VulkanTexture* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Texture : Cast is Wrong!\n");
		return nullptr;
	}

};