#pragma once
#include <iostream>

class VulkanTexture;

class IDevice;
class ISwapChain;
class IDepthRessource;
class ICommandPool;

class ITexture {

public:

	virtual void Create(IDevice* a_device, ISwapChain* a_swapChain, IDepthRessource* a_depthRessource, ICommandPool* a_commandPool) = 0;
	virtual void Destroy() = 0;

	virtual VulkanTexture* CastVulkan()
	{
		std::cout << "Wrong cast\n";
		return nullptr;
	}

};