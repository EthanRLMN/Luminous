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
    void Begin(const std::optional<std::function<void()>>& a_function) override;
    void End(const std::optional<std::function<void()>>& a_function) override;

    VkFormat FindDepthFormat(const VkPhysicalDevice& a_physicalDevice);
    VkFormat FindSupportedFormat(const VkPhysicalDevice& a_physicalDevice, const std::vector<VkFormat>& a_candidates, const VkImageTiling& a_tiling, const VkFormatFeatureFlags& a_features);
    VulkanRenderPass* CastVulkan() override { return this; }
    [[nodiscard]] VkRenderPass GetRenderPass() const { return m_renderPass; }

private:
    void FillColorAttachmentInfo(VkAttachmentDescription& a_colorAttachment, const VkFormat& a_swapChainImageFormat);
    void FillDepthAttachmentInfo(VkAttachmentDescription& a_depthAttachment, const VkFormat& a_depthFormat);
    void SetupSubpass(VkSubpassDescription& a_subpass, const VkAttachmentReference& a_colorAttachmentReference, const VkAttachmentReference& a_depthAttachmentReference);
    void SetupSubpassDependency(VkSubpassDependency& a_dependency);
    void SetupRenderPassCreateInfo(VkRenderPassCreateInfo& a_renderPassCreateInfo, const std::array<VkAttachmentDescription, 2>& a_attachments, const VkSubpassDescription& a_subpass, const VkSubpassDependency& a_dependency);

    VkRenderPass m_renderPass = nullptr;
};
