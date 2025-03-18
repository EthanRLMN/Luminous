#pragma once
#include <iostream>

class VulkanFrameBuffer;
class IDevice;
class ISwapChain;
class IRenderPass;
class IDepthResource;

class IFrameBuffer {
public:
	virtual ~IFrameBuffer() = default;

	virtual void Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass, IDepthResource* a_depthRessource) = 0;
	virtual void Destroy() = 0;

	virtual VulkanFrameBuffer* CastVulkan()
	{
		std::cout << "Wrong cast\n";
		return nullptr;
	}
};