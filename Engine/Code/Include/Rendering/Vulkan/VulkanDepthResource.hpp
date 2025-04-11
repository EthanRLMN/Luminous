#pragma once

#include <vulkan/vulkan.h>

#include "IDepthResource.hpp"

class VulkanDepthResource : public IDepthResource
{
public:
	void Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass) override;
	void Destroy(IDevice* a_device) override;

	VulkanDepthResource* CastVulkan() override { return this; }

	[[nodiscard]] virtual VkImage GetDepthImage() const { return m_depthImage; }
	[[nodiscard]] virtual VkDeviceMemory GetDepthImageMemory() const { return m_depthImageMemory; }
	[[nodiscard]] virtual VkImageView GetDepthImageView() const { return m_depthImageView; }

private:

	VkImage m_depthImage{ nullptr };
	VkDeviceMemory m_depthImageMemory{ nullptr };
	VkImageView m_depthImageView{ nullptr };
};
