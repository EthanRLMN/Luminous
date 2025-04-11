
#include "IMultiSampling.hpp"
#include "vulkan/vulkan.h"
#include "Struct/VulkanUtilities.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanDepthResource.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"

class VulkanMultiSampling : public IMultiSampling
{
public:
    void Create(IDevice* a_device) override;
    void Destroy(IDevice* a_device) override;

    VkSampleCountFlagBits GetMaxUsableSampleCount(IDevice* a_device);
    void CreateColorResources(IDevice* a_device, ISwapChain* a_swapchain);

private:

    VkImage m_colorImage;
    VkDeviceMemory m_colorImageMemory;
    VkImageView m_colorImageView;
};
