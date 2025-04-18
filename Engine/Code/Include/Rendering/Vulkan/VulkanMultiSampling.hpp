#pragma once

#include "vulkan/vulkan.h"

#include "IMultiSampling.hpp"

class VulkanMultiSampling final : public IMultiSampling
{
public:
    void Create(IDevice* a_device, ISwapChain* a_swapchain) override;
    void Destroy(IDevice* a_device) override;
    void SetSampleCount(IDevice* a_device, const SamplingCount& a_samplingCount) override;
    VulkanMultiSampling* CastVulkan() override { return this; }

    void CreateColorResources(IDevice* a_device, ISwapChain* a_swapchain);

    static VkSampleCountFlagBits GetMaxUsableSampleCount(IDevice* a_device) ;
    [[nodiscard]] VkImageView GetColorImageView() const { return m_colorImageView; }

private:
    VkImage m_colorImage{ nullptr };
    VkDeviceMemory m_colorImageMemory{ nullptr };
    VkImageView m_colorImageView{ nullptr };
};
