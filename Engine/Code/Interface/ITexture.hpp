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

	bool Create(IResourceManager* a_manager, IResourceParams a_params) override { return false; };
    void Destroy(IDevice* a_device) override { };

	virtual VulkanTexture* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Texture : Cast is Wrong!\n");
		return nullptr;
	}

};