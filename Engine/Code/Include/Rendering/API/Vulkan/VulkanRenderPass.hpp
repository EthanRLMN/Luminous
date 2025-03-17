#pragma once

#include <iostream>
#include <set>
#include <vulkan/vulkan.h>
#include "Rendering/API/Vulkan/VulkanSurface.hpp"
#include "Rendering/API/Vulkan/VulkanDevice.hpp"
#include "Rendering/API/Vulkan/VulkanSwapChain.hpp"
#include "IRenderPass.hpp"

class VulkanRenderPass : public IRenderPass
{
public :
    void Create(ISwapChain* a_swapchain, IDevice* a_device) override;
    void Destroy(IDevice* _device) override;

    void CreateRenderPass(ISwapChain* a_swapchain, IDevice* a_device);

    VkFormat FindDepthFormat(VkPhysicalDevice a_physicalDevice);

    VkFormat FindSupportedFormat(VkPhysicalDevice a_physicalDevice, const std::vector<VkFormat>& a_candidates, VkImageTiling a_tiling, VkFormatFeatureFlags a_features);

    VulkanRenderPass* CastVulkan() override { return this; }

    [[nodiscard]] virtual VkRenderPass GetInstance() const { return m_renderPass; }

private:
    VkRenderPass m_renderPass = VK_NULL_HANDLE;
};
