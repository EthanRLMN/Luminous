#include "IDevice.hpp"

#include "Rendering/Vulkan/VulkanMultiSampling.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"


void VulkanMultiSampling::Create(IDevice* a_device, ISwapChain* a_swapchain)
{
    CreateColorResources(a_device, a_swapchain);
}


void VulkanMultiSampling::Destroy(IDevice* a_device)
{
    vkDestroyImageView(a_device->CastVulkan()->GetDevice(), m_colorImageView, nullptr);
    vkDestroyImage(a_device->CastVulkan()->GetDevice(), m_colorImage, nullptr);
    vkFreeMemory(a_device->CastVulkan()->GetDevice(), m_colorImageMemory, nullptr);
}


void VulkanMultiSampling::SetSampleCount(IDevice* a_device, const SamplingCount& a_samplingCount)
{
    const VkSampleCountFlagBits l_sampleCount = CastVulkanSample(a_samplingCount);
    const VkSampleCountFlagBits l_maxCount = GetMaxUsableSampleCount(a_device);
    if (l_sampleCount > l_maxCount)
    {
        a_device->CastVulkan()->SetMSAASamples(l_maxCount);
        DEBUG_LOG_INFO("Tried to set a too high sample count, sample count has been set to max.");
    } else
    {
        a_device->CastVulkan()->SetMSAASamples(l_sampleCount);
        DEBUG_LOG_INFO("Sample count has been set to {}", static_cast<int>(l_sampleCount));
    }
}


VkSampleCountFlagBits VulkanMultiSampling::GetMaxUsableSampleCount(IDevice* a_device)
{
    VkPhysicalDeviceProperties l_properties{};
    vkGetPhysicalDeviceProperties(a_device->CastVulkan()->GetPhysicalDevice(), &l_properties);
    const VkSampleCountFlags l_maxSupportedCount = l_properties.limits.framebufferColorSampleCounts & l_properties.limits.framebufferDepthSampleCounts;
    constexpr std::array<VkSampleCountFlagBits, 7> l_sampleCounts = {
        VK_SAMPLE_COUNT_64_BIT,
        VK_SAMPLE_COUNT_32_BIT,
        VK_SAMPLE_COUNT_16_BIT,
        VK_SAMPLE_COUNT_8_BIT,
        VK_SAMPLE_COUNT_4_BIT,
        VK_SAMPLE_COUNT_2_BIT
    };

    for (const VkSampleCountFlagBits l_count : l_sampleCounts)
        if (l_maxSupportedCount & l_count)
            return l_count;

    return VK_SAMPLE_COUNT_1_BIT;
}


void VulkanMultiSampling::CreateColorResources(IDevice* a_device, ISwapChain* a_swapchain)
{
    const VulkanDevice& l_device = *a_device->CastVulkan();
    const VulkanSwapChain& l_swapchain = *a_swapchain->CastVulkan();

    VulkanSwapChain::CreateImage(l_device.GetDevice(), l_device.GetPhysicalDevice(), l_swapchain.GetSwapChainExtent().width, l_swapchain.GetSwapChainExtent().height, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_colorImage, m_colorImageMemory, l_device.GetMSAASamples(), 1);
    m_colorImageView = VulkanSwapChain::CreateImageView(m_colorImage, l_device.GetDevice(), VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, 1);
}