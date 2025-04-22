#pragma once

#include <array>

#include "vulkan/vulkan.h"

#include "IMultiSampling.hpp"

static constexpr std::array<VkSampleCountFlagBits, 7> VkSampleCount = {
    VK_SAMPLE_COUNT_1_BIT,
    VK_SAMPLE_COUNT_2_BIT,
    VK_SAMPLE_COUNT_4_BIT,
    VK_SAMPLE_COUNT_8_BIT,
    VK_SAMPLE_COUNT_16_BIT,
    VK_SAMPLE_COUNT_32_BIT,
    VK_SAMPLE_COUNT_64_BIT
};

static VkSampleCountFlagBits CastVulkanSample(const SamplingCount& a_msaa)
{
    const int l_msaaIndex = static_cast<int>(a_msaa);
    return VkSampleCount[l_msaaIndex - 1];
}

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
