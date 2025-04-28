#include "Rendering/Vulkan/VulkanMultiSampling.hpp"

#include "IDevice.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"

void VulkanMultiSampling::Create(IDevice* a_device, ISwapChain* a_swapchain) { a_device->CastVulkan()->SetMSAASamples(GetMaxUsableSampleCount(a_device)); }

void VulkanMultiSampling::SetSampleCount(IDevice* a_device, const VkSampleCountFlagBits a_sampleCount)
{
    const VkSampleCountFlagBits& l_maxCount = GetMaxUsableSampleCount(a_device);
    if (a_sampleCount > l_maxCount)
    {
        a_device->CastVulkan()->SetMSAASamples(l_maxCount);
        DEBUG_LOG_INFO("Tried to set a too high sample count, sample count has been set to max.");
    } else
    {
        a_device->CastVulkan()->SetMSAASamples(a_sampleCount);
        DEBUG_LOG_INFO("Sample count has been set to {}", static_cast<int>(a_sampleCount));
    }
}


void VulkanMultiSampling::Destroy(IDevice* a_device)
{
    vkDestroyImageView(a_device->CastVulkan()->GetDevice(), m_colorImageView, nullptr);
    vkDestroyImage(a_device->CastVulkan()->GetDevice(), m_colorImage, nullptr);
    vkFreeMemory(a_device->CastVulkan()->GetDevice(), m_colorImageMemory, nullptr);
}

VkSampleCountFlagBits VulkanMultiSampling::GetMaxUsableSampleCount(IDevice* a_device)
{
    VkPhysicalDeviceProperties l_properties{};
    vkGetPhysicalDeviceProperties(a_device->CastVulkan()->GetPhysicalDevice(), &l_properties);

    const VkSampleCountFlags l_counts = l_properties.limits.framebufferColorSampleCounts & l_properties.limits.framebufferDepthSampleCounts;
    static const VkSampleCountFlagBits l_sampleCounts[] = {
        VK_SAMPLE_COUNT_64_BIT,
        VK_SAMPLE_COUNT_32_BIT,
        VK_SAMPLE_COUNT_16_BIT,
        VK_SAMPLE_COUNT_8_BIT,
        VK_SAMPLE_COUNT_4_BIT,
        VK_SAMPLE_COUNT_2_BIT
    };

    for (const VkSampleCountFlagBits l_count : l_sampleCounts)
    {
        if (l_counts & l_count)
            return l_count;
    }

    return VK_SAMPLE_COUNT_1_BIT;
}

void VulkanMultiSampling::CreateColorResources(IDevice* a_device, ISwapChain* a_swapchain)
{
    const VkFormat l_colorFormat = a_swapchain->CastVulkan()->GetSwapChainImageFormat();

    a_swapchain->CastVulkan()->CreateImage(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), a_swapchain->CastVulkan()->GetSwapChainExtent().width, a_swapchain->CastVulkan()->GetSwapChainExtent().height, l_colorFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_colorImage, m_colorImageMemory, a_device->CastVulkan()->GetMSAASamples());
    m_colorImageView = a_swapchain->CastVulkan()->CreateImageView(m_colorImage, a_device->CastVulkan()->GetDevice(), l_colorFormat, VK_IMAGE_ASPECT_COLOR_BIT);

}


