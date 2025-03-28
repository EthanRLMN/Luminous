#pragma once

#include <vulkan/vulkan.h>

#include "IDepthResource.hpp"

class VulkanDepthResource : public IDepthResource
{
public:
	void Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass) override;
	void Destroy() override;

	VulkanDepthResource* CastVulkan() override { return this; }

	void CreateImage(VkDevice a_device, VkPhysicalDevice a_physicalDevice, uint32_t a_width, uint32_t a_height, VkFormat a_format, VkImageTiling a_tiling, VkImageUsageFlags a_usage, VkMemoryPropertyFlags a_properties, VkImage& a_image, VkDeviceMemory& a_imageMemory);

	uint32_t FindMemoryType(VkPhysicalDevice a_physicalDevice, uint32_t a_typeFilter, VkMemoryPropertyFlags a_properties);

	[[nodiscard]] virtual VkImage GetDepthImage() const { return m_depthImage; }
	[[nodiscard]] virtual VkDeviceMemory GetDepthImageMemory() const { return m_depthImageMemory; }
	[[nodiscard]] virtual VkImageView GetDepthImageView() const { return m_depthImageView; }

private:
	VkImage m_depthImage{ VK_NULL_HANDLE };
	VkDeviceMemory m_depthImageMemory{ VK_NULL_HANDLE };
	VkImageView m_depthImageView{ VK_NULL_HANDLE };
};
