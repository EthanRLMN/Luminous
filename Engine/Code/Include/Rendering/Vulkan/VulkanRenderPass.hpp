#pragma once

#include <functional>
#include <vector>
#include <vulkan/vulkan.h>

#include "IRenderPass.hpp"


class VulkanRenderPass final : public IRenderPass
{
public :
    void Create(ISwapChain* a_swapChain, IDevice* a_device) override;
    void Destroy(IDevice* a_device) override;

    void CreateEditorPass(ISwapChain* a_swapChain, IDevice* a_device);
    static VkFormat FindDepthFormat(const VkPhysicalDevice& a_physicalDevice);
    static VkFormat FindSupportedFormat(const VkPhysicalDevice& a_physicalDevice, const std::vector<VkFormat>& a_candidates, const VkImageTiling& a_tiling, const VkFormatFeatureFlags& a_features);
    VulkanRenderPass* CastVulkan() override { return this; }
    [[nodiscard]] VkRenderPass GetRenderPass() const { return m_renderPass; }

private:
    static void FillColorAttachmentInfo(VkAttachmentDescription& a_colorAttachment, const VkFormat& a_swapChainImageFormat, const VkSampleCountFlagBits& a_samples);
    static void FillDepthAttachmentInfo(VkAttachmentDescription& a_depthAttachment, const VkFormat& a_depthFormat, const VkSampleCountFlagBits& a_samples);
    static void FillColorAttachmentResolveInfo(VkAttachmentDescription& a_colorAttachmentResolve, const VkFormat& a_swapchainImageFormat);
    static void SetupSubpass(VkSubpassDescription& a_subpass, const VkAttachmentReference& a_colorAttachmentReference, const VkAttachmentReference& a_depthAttachmentReference);
    static void SetupSubpassDependency(VkSubpassDependency& a_dependency);
    static void SetupRenderPassCreateInfo(VkRenderPassCreateInfo& a_renderPassCreateInfo, const std::vector<VkAttachmentDescription>& a_attachments, const VkSubpassDescription& a_subpass, const VkSubpassDependency& a_dependency);

    VkRenderPass m_renderPass = nullptr;
};
