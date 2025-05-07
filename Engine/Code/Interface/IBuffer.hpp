#pragma once

#include "Logger.hpp"

class VulkanBuffer;
class IDevice;
class ITexture;
class ICommandPool;
class IDepthResource;
class IMesh;
class ISwapChain;

class IBuffer
{
public:
	virtual ~IBuffer() = default;

	virtual void Create(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, ISwapChain* a_swapChain, std::vector<IMesh*> a_meshes) = 0;
	virtual void Destroy(IDevice* a_device) = 0;

	virtual VulkanBuffer* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Buffer : Cast is Wrong!\n");
		return nullptr;
	}

};
