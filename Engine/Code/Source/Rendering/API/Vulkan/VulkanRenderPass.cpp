#include "Rendering/API/Vulkan/VulkanRenderPass.hpp"

#include <array>
#include <vector>

#include "IDevice.hpp"
#include "ISwapChain.hpp"
#include "Rendering/API/Vulkan/VulkanDevice.hpp"
#include "Rendering/API/Vulkan/VulkanSwapChain.hpp"

void VulkanRenderPass::Create(ISwapChain* a_swapChain, IDevice* a_device)
{
	CreateRenderPass(a_swapChain, a_device);
}

void VulkanRenderPass::Destroy(IDevice* a_device)
{
}

void VulkanRenderPass::CreateRenderPass(ISwapChain* a_swapChain, IDevice* a_device)
{
	VkAttachmentDescription l_colorAttachment = {};
	l_colorAttachment.format = a_swapChain->CastVulkan()->GetSwapChainImageFormat();
	l_colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	l_colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	l_colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	l_colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	l_colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	l_colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	l_colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentDescription l_depthAttachment{};
	l_depthAttachment.format = FindDepthFormat(a_device->CastVulkan()->GetPhysicalDevice());
	l_depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	l_depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	l_depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	l_depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	l_depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	l_depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	l_depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentReference l_colorAttachmentReference = {};
	l_colorAttachmentReference.attachment = 0;
	l_colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReference l_depthAttachmentReference = {};
	l_depthAttachmentReference.attachment = 1;
	l_depthAttachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkSubpassDescription l_subpass = {};
	l_subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	l_subpass.colorAttachmentCount = 1;
	l_subpass.pColorAttachments = &l_colorAttachmentReference;
	l_subpass.pDepthStencilAttachment = &l_depthAttachmentReference;

	VkSubpassDependency l_dependency{};
	l_dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	l_dependency.dstSubpass = 0;
	l_dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT |
	                            VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	l_dependency.srcAccessMask = 0;
	l_dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT |
	                            VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	l_dependency.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

	const std::array<VkAttachmentDescription, 2> l_attachments = {l_colorAttachment, l_depthAttachment};

	VkRenderPassCreateInfo l_renderPassCreateInfo = {};
	l_renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	l_renderPassCreateInfo.attachmentCount = static_cast<uint32_t>(l_attachments.size());
	l_renderPassCreateInfo.pAttachments = l_attachments.data();
	l_renderPassCreateInfo.subpassCount = 1;
	l_renderPassCreateInfo.pSubpasses = &l_subpass;
	l_renderPassCreateInfo.dependencyCount = 1;
	l_renderPassCreateInfo.pDependencies = &l_dependency;

	const VkResult l_result = vkCreateRenderPass(a_device->CastVulkan()->GetDevice(), &l_renderPassCreateInfo, nullptr,
	                                             &m_renderPass);

	if (l_result != VK_SUCCESS)
		throw std::runtime_error("Failed to create a render pass");
}

VkFormat VulkanRenderPass::FindDepthFormat(const VkPhysicalDevice a_physicalDevice)
{
	return FindSupportedFormat(a_physicalDevice,
	                           {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
	                           VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}


VkFormat VulkanRenderPass::FindSupportedFormat(const VkPhysicalDevice a_physicalDevice,
                                               const std::vector<VkFormat>& a_candidates, const VkImageTiling a_tiling,
                                               const VkFormatFeatureFlags a_features)
{
	for (const VkFormat l_format: a_candidates)
	{
		VkFormatProperties l_props;
		vkGetPhysicalDeviceFormatProperties(a_physicalDevice, l_format, &l_props);

		if (a_tiling == VK_IMAGE_TILING_LINEAR && (l_props.linearTilingFeatures & a_features) == a_features)
			return l_format;

		if (a_tiling == VK_IMAGE_TILING_OPTIMAL && (l_props.optimalTilingFeatures & a_features) == a_features)
			return l_format;
	}
	std::cout << " failed to find supported format" << std::endl;
	return VK_FORMAT_UNDEFINED;
}

