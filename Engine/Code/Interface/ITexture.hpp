#pragma once
#include <iostream>

class VulkanTexture;

class IDevice;
class ISwapChain;
class IDepthResource;
class ICommandPool;

class ITexture {

public:
	virtual ~ITexture() = default;

	virtual void Create(IDevice* a_device, ISwapChain* a_swapChain, IDepthResource* a_depthResource, ICommandPool* a_commandPool) = 0;
	virtual void Destroy() = 0;

	virtual VulkanTexture* CastVulkan()
	{
		std::cout << "Wrong cast\n";
		return nullptr;
	}

};