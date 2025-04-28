#pragma once

#include <array>
#include <vulkan/vulkan.h>

enum class MULTISAMPLING_SAMPLES
{
    MULTISAMPLING_SAMPLECOUNT_1 = 1,
    MULTISAMPLING_SAMPLECOUNT_2 = 2,
    MULTISAMPLING_SAMPLECOUNT_4,
    MULTISAMPLING_SAMPLECOUNT_8,
    MULTISAMPLING_SAMPLECOUNT_16,
    MULTISAMPLING_SAMPLECOUNT_32,
    MULTISAMPLING_SAMPLECOUNT_64
};

inline VkSampleCountFlagBits CastVulkanSample(const MULTISAMPLING_SAMPLES a_msaa)
{
    const int l_msaaIndex = static_cast<int>(a_msaa);
    static constexpr std::array<VkSampleCountFlagBits, 7> l_vkSamples =
    {
        VK_SAMPLE_COUNT_1_BIT,
        VK_SAMPLE_COUNT_2_BIT,
        VK_SAMPLE_COUNT_4_BIT,
        VK_SAMPLE_COUNT_8_BIT,
        VK_SAMPLE_COUNT_16_BIT,
        VK_SAMPLE_COUNT_32_BIT,
        VK_SAMPLE_COUNT_64_BIT
    };

    return l_vkSamples[l_msaaIndex - 1];
}
