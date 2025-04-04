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
	virtual ~ITexture() = default;

	bool Create(IResourceManager* a_manager, IResourceParams a_params) override { return false; };
    void Destroy(...) override { return; };

	virtual VulkanTexture* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Texture : Cast is Wrong!\n");
		return nullptr;
	}

};