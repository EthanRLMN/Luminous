#pragma once

#include "IFrameBuffer.hpp"

class VulkanFrameBuffer final : public IFrameBuffer
{
public:
	void Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass,
	            IDepthResource* a_depthResource) override;
	void Destroy() override;

	VulkanFrameBuffer* CastVulkan() override { return this; }
};
