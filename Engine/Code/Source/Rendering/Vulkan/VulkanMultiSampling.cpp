#include "Rendering/Vulkan/VulkanMultiSampling.hpp"


void VulkanMultiSampling::Create(IDevice* a_device)
{
    a_device->CastVulkan()->SetMSAASamples(GetMaxUsableSampleCount(a_device));
}

void VulkanMultiSampling::Destroy(IDevice* a_device)
{
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

void VulkanMultiSampling::CreateColorResources(IDevice* a_device ,IDepthResource* a_depthResource, ISwapChain* a_swapchain)
{
    //VkFormat l_colorFormat = a_swapchain->CastVulkan()->GetSwapChainImageFormat();

    //a_depthResource->CastVulkan()->CreateImage(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), a_swapchain->CastVulkan()->GetSwapChainExtent().width, a_swapchain->CastVulkan()->GetSwapChainExtent().height, l_colorFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_colorImage, m_colorImageMemory, a_device->CastVulkan()->GetMSAASamples());
   // m_colorImageView = createImageView(colorImage, colorFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);

}
