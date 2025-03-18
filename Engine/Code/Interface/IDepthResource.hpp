#pragma once
#include <iostream>

class VulkanDepthRessource;

class IDevice;
class ISwapChain;
class IRenderPass;

class IDepthResource
{
public:
	virtual ~IDepthResource() = default;

	virtual void Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass) = 0;
	virtual void Destroy() = 0;

	virtual VulkanDepthRessource* CastVulkan()
	{
		std::cout << "Wrong cast\n";
		return nullptr;
	}
};
