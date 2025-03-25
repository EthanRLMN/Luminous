#include "IDepthResource.hpp"
#include "IDevice.hpp"
#include "IRenderPass.hpp"
#include "ISwapChain.hpp"

#include "Rendering/Vulkan/VulkanFrameBuffer.hpp"
#include "Rendering/Vulkan/VulkanDepthResource.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"

void VulkanFrameBuffer::Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass,
                               IDepthResource* a_depthResource)
{
	a_swapChain->CastVulkan()->SetSwapChainFrameBufferSize(a_swapChain->CastVulkan()->GetSwapChainImageViews().size());

	const VulkanSwapChain* l_vulkanSwapChain = a_swapChain->CastVulkan();
	for (size_t i = 0; i < l_vulkanSwapChain->GetSwapChainImageViews().size(); ++i)
	{
		std::array<VkImageView, 2> l_attachments = {
			l_vulkanSwapChain->GetSwapChainImageViews()[i],
			a_depthResource->CastVulkan()->GetDepthImageView()
		};

		VkFramebufferCreateInfo l_framebufferCreateInfo = {};
		l_framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		l_framebufferCreateInfo.renderPass = a_renderPass->CastVulkan()->GetRenderPass();
		l_framebufferCreateInfo.attachmentCount = static_cast<uint32_t>(l_attachments.size());
		l_framebufferCreateInfo.pAttachments = l_attachments.data();
		l_framebufferCreateInfo.width = l_vulkanSwapChain->GetSwapChainExtent().width;
		l_framebufferCreateInfo.height = l_vulkanSwapChain->GetSwapChainExtent().height;
		l_framebufferCreateInfo.layers = 1;

		const VkResult l_result = vkCreateFramebuffer(a_device->CastVulkan()->GetDevice(), &l_framebufferCreateInfo,
		                                              nullptr, &l_vulkanSwapChain->GetSwapChainFrameBuffers()[i]);;
		if (l_result != VK_SUCCESS)
			throw std::runtime_error("Failed to create framebuffer");
	}
}

void VulkanFrameBuffer::Destroy()
{
}
