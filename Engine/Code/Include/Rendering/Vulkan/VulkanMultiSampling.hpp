
#pragma once

#include "vulkan/vulkan.h"
#include "Struct/VulkanUtilities.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanDepthResource.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"
#include "IMultiSampling.hpp"
#include "vulkan/vulkan.hpp"

class VulkanMultiSampling : public IMultiSampling
{
public:
    void Create(IDevice* a_device, ISwapChain* a_swapchain) override;
    void Destroy(IDevice* a_device) override;

    VkSampleCountFlagBits GetMaxUsableSampleCount(IDevice* a_device);
    void CreateColorResources(IDevice* a_device, ISwapChain* a_swapchain);
    void SetSampleCount(IDevice* a_device, VkSampleCountFlagBits a_sampleCount);

     VulkanMultiSampling* CastVulkan() override { return this; }

     inline VkImageView GetColorImageView() { return m_colorImageView; }

private:

    VkImage m_colorImage;
    VkDeviceMemory m_colorImageMemory;
    VkImageView m_colorImageView;
};
