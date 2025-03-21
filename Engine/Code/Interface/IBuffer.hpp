#pragma once
#include <Logger.hpp>

class VulkanBuffer;
class IDevice;
class ITexture;
class ICommandPool;
class IDepthResource;


class IBuffer
{
public:
	virtual ~IBuffer() = default;

	virtual void Create(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, IDepthResource* a_depthResource) = 0;
	virtual void Destroy() = 0;

	virtual VulkanBuffer* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Buffer : Cast is Wrong!\n");
		return nullptr;
	}

};
