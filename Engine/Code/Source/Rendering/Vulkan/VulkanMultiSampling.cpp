#include "Rendering/Vulkan/VulkanMultiSampling.hpp"


void VulkanMultiSampling::Create(IDevice* a_device)
{
    //a_device->CastVulkan()->SetMSAASamples(GetMaxUsableSampleCount(a_device));
}

void VulkanMultiSampling::Destroy(IDevice* a_device)
{
    vkDestroyImageView(a_device->CastVulkan()->GetDevice(), m_colorImageView, nullptr);
    vkDestroyImage(a_device->CastVulkan()->GetDevice(), m_colorImage, nullptr);
    vkFreeMemory(a_device->CastVulkan()->GetDevice(), m_colorImageMemory, nullptr);
}

VkSampleCountFlagBits VulkanMultiSampling::GetMaxUsableSampleCount(IDevice* a_device)
{
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(a_device->CastVulkan()->GetPhysicalDevice(), &physicalDeviceProperties);

    VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;
    if (counts & VK_SAMPLE_COUNT_64_BIT)
    {
        return VK_SAMPLE_COUNT_64_BIT;
    }
    if (counts & VK_SAMPLE_COUNT_32_BIT)
    {
        return VK_SAMPLE_COUNT_32_BIT;
    }
    if (counts & VK_SAMPLE_COUNT_16_BIT)
    {
        return VK_SAMPLE_COUNT_16_BIT;
    }
    if (counts & VK_SAMPLE_COUNT_8_BIT)
    {
        return VK_SAMPLE_COUNT_8_BIT;
    }
    if (counts & VK_SAMPLE_COUNT_4_BIT)
    {
        return VK_SAMPLE_COUNT_4_BIT;
    }
    if (counts & VK_SAMPLE_COUNT_2_BIT)
    {
        return VK_SAMPLE_COUNT_2_BIT;
    }

    return VK_SAMPLE_COUNT_1_BIT;
}

void VulkanMultiSampling::CreateColorResources(IDevice* a_device , ISwapChain* a_swapchain)
{
    VkFormat l_colorFormat = a_swapchain->CastVulkan()->GetSwapChainImageFormat();

    a_swapchain->CastVulkan()->CreateImage(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), a_swapchain->CastVulkan()->GetSwapChainExtent().width, a_swapchain->CastVulkan()->GetSwapChainExtent().height, l_colorFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_colorImage, m_colorImageMemory, a_device->CastVulkan()->GetMSAASamples());
    m_colorImageView = a_swapchain->CastVulkan()->CreateImageView(m_colorImage, a_device->CastVulkan()->GetDevice(), l_colorFormat, VK_IMAGE_ASPECT_COLOR_BIT);

}
