#pragma once

#include "Logger.hpp"
#include "ResourceManager/Resource.hpp"

class VulkanTexture;

class IDevice;
class ISwapChain;
class IDepthResource;
class ICommandPool;

class ITexture : public IResource 
{

public:
    ~ITexture() override = default;

	bool Create(const IResourceParams& a_params) override { static_cast<void>(a_params); return false; };
    void Destroy(IDevice* a_device) override { static_cast<void>(a_device); };

	virtual VulkanTexture* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Texture : Cast is Wrong!\n");
		return nullptr;
	}

};