#pragma once

#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>
#include "IRenderPass.hpp"

class VulkanRenderPass final : public IRenderPass
{
public :
    void Create(ISwapChain* a_swapChain, IDevice* a_device) override;
    void Destroy(IDevice* a_device) override;

    void CreateRenderPass(ISwapChain* a_swapChain, IDevice* a_device);

    VkFormat FindDepthFormat(VkPhysicalDevice a_physicalDevice);

    VkFormat FindSupportedFormat(VkPhysicalDevice a_physicalDevice, const std::vector<VkFormat>& a_candidates, VkImageTiling a_tiling, VkFormatFeatureFlags a_features);

    VulkanRenderPass* CastVulkan() override { return this; }

    [[nodiscard]] virtual VkRenderPass GetRenderPass() const { return m_renderPass; }

private:
    VkRenderPass m_renderPass = nullptr;
};
