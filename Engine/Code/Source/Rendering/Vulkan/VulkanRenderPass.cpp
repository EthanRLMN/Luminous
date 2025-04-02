#include <array>
#include <vector>

#include "IDevice.hpp"
#include "ISwapChain.hpp"

#include "Rendering/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"


void VulkanRenderPass::Create(ISwapChain* a_swapChain, IDevice* a_device)
{
    CreateRenderPass(a_swapChain, a_device);
    DEBUG_LOG_INFO("Vulkan RenderPass : RenderPass created!\n");
}


void VulkanRenderPass::Destroy(IDevice* a_device)
{
    vkDestroyRenderPass(a_device->CastVulkan()->GetDevice(), m_renderPass, nullptr);
    DEBUG_LOG_INFO("Vulkan RenderPass : Destroy RenderPass!\n");
}


void VulkanRenderPass::CreateRenderPass(ISwapChain* a_swapChain, IDevice* a_device)
{
    VkAttachmentDescription l_colorAttachment = {};
    FillColorAttachmentInfo(l_colorAttachment, a_swapChain->CastVulkan()->GetSwapChainImageFormat());

    VkAttachmentDescription l_depthAttachment{};
    FillDepthAttachmentInfo(l_depthAttachment, FindDepthFormat(a_device->CastVulkan()->GetPhysicalDevice()));

    VkAttachmentReference l_colorAttachmentReference = {};
    l_colorAttachmentReference.attachment = 0;
    l_colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference l_depthAttachmentReference = {};
    l_depthAttachmentReference.attachment = 1;
    l_depthAttachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkSubpassDescription l_subpass = {};
    SetupSubpass(l_subpass, l_colorAttachmentReference, l_depthAttachmentReference);

    VkSubpassDependency l_dependency{};
    SetupSubpassDependency(l_dependency);

    const std::array<VkAttachmentDescription, 2> l_attachments = { l_colorAttachment, l_depthAttachment };
    VkRenderPassCreateInfo l_renderPassCreateInfo = {};
    SetupRenderPassCreateInfo(l_renderPassCreateInfo, l_attachments, l_subpass, l_dependency);

    const VkResult l_result = vkCreateRenderPass(a_device->CastVulkan()->GetDevice(), &l_renderPassCreateInfo, nullptr, &m_renderPass);
    if (l_result != VK_SUCCESS)
        DEBUG_LOG_ERROR("Failed to create a render pass\n");
}


VkFormat VulkanRenderPass::FindDepthFormat(const VkPhysicalDevice a_physicalDevice)
{
    return FindSupportedFormat(a_physicalDevice, { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT }, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}


VkFormat VulkanRenderPass::FindSupportedFormat(const VkPhysicalDevice a_physicalDevice, const std::vector<VkFormat>& a_candidates, const VkImageTiling a_tiling, const VkFormatFeatureFlags a_features)
{
    for (const VkFormat l_format : a_candidates)
    {
        VkFormatProperties l_props;
        vkGetPhysicalDeviceFormatProperties(a_physicalDevice, l_format, &l_props);

        if (a_tiling == VK_IMAGE_TILING_LINEAR && (l_props.linearTilingFeatures & a_features) == a_features)
            return l_format;

        if (a_tiling == VK_IMAGE_TILING_OPTIMAL && (l_props.optimalTilingFeatures & a_features) == a_features)
            return l_format;
    }

    DEBUG_LOG_ERROR("Vulkan RenderPass : Failed to find supported file format!\n");
    return VK_FORMAT_UNDEFINED;
}

void VulkanRenderPass::FillColorAttachmentInfo(VkAttachmentDescription& a_colorAttachment, const VkFormat& a_swapChainImageFormat)
{
    a_colorAttachment.format = a_swapChainImageFormat;
    a_colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    a_colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    a_colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    a_colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    a_colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    a_colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    a_colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
}

void VulkanRenderPass::FillDepthAttachmentInfo(VkAttachmentDescription& a_depthAttachment, const VkFormat& a_depthFormat)
{
    a_depthAttachment.format = a_depthFormat;
    a_depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    a_depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    a_depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    a_depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    a_depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    a_depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    a_depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
}

void VulkanRenderPass::SetupSubpass(VkSubpassDescription& a_subpass, const VkAttachmentReference& a_colorAttachmentReference, const VkAttachmentReference& a_depthAttachmentReference)
{
    a_subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    a_subpass.colorAttachmentCount = 1;
    a_subpass.pColorAttachments = &a_colorAttachmentReference;
    a_subpass.pDepthStencilAttachment = &a_depthAttachmentReference;
}

void VulkanRenderPass::SetupSubpassDependency(VkSubpassDependency& a_dependency)
{
    a_dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    a_dependency.dstSubpass = 0;
    a_dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    a_dependency.srcAccessMask = 0;
    a_dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    a_dependency.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
}

void VulkanRenderPass::SetupRenderPassCreateInfo(VkRenderPassCreateInfo& a_renderPassCreateInfo, const std::array<VkAttachmentDescription, 2>& a_attachments, const VkSubpassDescription& a_subpass, const VkSubpassDependency& a_dependency)
{
    a_renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    a_renderPassCreateInfo.attachmentCount = static_cast<uint32_t>(a_attachments.size());
    a_renderPassCreateInfo.pAttachments = a_attachments.data();
    a_renderPassCreateInfo.subpassCount = 1;
    a_renderPassCreateInfo.pSubpasses = &a_subpass;
    a_renderPassCreateInfo.dependencyCount = 1;
    a_renderPassCreateInfo.pDependencies = &a_dependency;
}
