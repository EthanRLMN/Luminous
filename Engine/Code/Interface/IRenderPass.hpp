#pragma once

class VulkanRenderPass;
class ISwapChain;
class IDevice;

class IRenderPass
{
public:
	virtual ~IRenderPass() = default;

	virtual void Create(ISwapChain* a_swapchain, IDevice* a_device) = 0;

	virtual void Destroy(IDevice* _device) = 0;
};
