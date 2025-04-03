#pragma once

#include "vulkan/vulkan.hpp"

#include "IFrameBuffer.hpp"


class VulkanFrameBuffer final : public IFrameBuffer
{
public:
	void Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass, IDepthResource* a_depthResource) override;
	void Destroy(IDevice* a_device) override;

	[[nodiscard]] std::vector<VkFramebuffer> GetFrameBuffers() const { return m_frameBuffers; }

	VulkanFrameBuffer* CastVulkan() override { return this; }

	void GetFrameBuffersSize(const size_t a_size);


private:
	std::vector<VkFramebuffer> m_frameBuffers { nullptr };
};
