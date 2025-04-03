#pragma once

#include <vulkan/vulkan.h>

#include "IDepthResource.hpp"


class VulkanDepthResource : public IDepthResource
{
public:
    void Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass) override;
    void Destroy(IDevice* a_device) override;
    VulkanDepthResource* CastVulkan() override { return this; }

    void CreateImage(const VkDevice& a_device, const VkPhysicalDevice& a_physicalDevice, const uint32_t& a_width, const uint32_t& a_height, const VkFormat& a_format, const VkImageTiling& a_tiling, const VkImageUsageFlags& a_usage, const VkMemoryPropertyFlags& a_properties, VkImage& a_image, VkDeviceMemory& a_imageMemory);
    uint32_t FindMemoryType(const VkPhysicalDevice& a_physicalDevice, const uint32_t& a_typeFilter, const VkMemoryPropertyFlags& a_properties);

    [[nodiscard]] virtual VkImage GetDepthImage() const { return m_depthImage; }
    [[nodiscard]] virtual VkDeviceMemory GetDepthImageMemory() const { return m_depthImageMemory; }
    [[nodiscard]] virtual VkImageView GetDepthImageView() const { return m_depthImageView; }

private:
    void FillImageInfo(const VkDevice& a_device, const uint32_t& a_width, const uint32_t& a_height, const VkFormat& a_format, const VkImageTiling& a_tiling, const VkImageUsageFlags& a_usage, VkImage& a_image);

    VkImage m_depthImage{ nullptr };
    VkDeviceMemory m_depthImageMemory{ nullptr };
    VkImageView m_depthImageView{ nullptr };
};
