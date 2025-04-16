#pragma once

#include "vulkan/vulkan.h"

#include "IMultiSampling.hpp"

class VulkanMultiSampling : public IMultiSampling
{
public:
    void Create(IDevice* a_device, ISwapChain* a_swapchain) override;
    void Destroy(IDevice* a_device) override;

    VkSampleCountFlagBits GetMaxUsableSampleCount(IDevice* a_device);
    void CreateColorResources(IDevice* a_device, ISwapChain* a_swapchain);
    void SetSampleCount(IDevice* a_device, VkSampleCountFlagBits a_sampleCount);

     VulkanMultiSampling* CastVulkan() override { return this; }

    VkImageView GetColorImageView() const { return m_colorImageView; }

private:

    VkImage m_colorImage { nullptr };
    VkDeviceMemory m_colorImageMemory { nullptr };
    VkImageView m_colorImageView { nullptr };
};
