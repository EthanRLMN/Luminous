#include "Rendering/API/Vulkan/VulkanFrameBuffer.hpp"

void VulkanFrameBuffer::Create(IDevice* a_device, ISwapChain* a_swapChain , IRenderPass* a_renderPass, IDepthRessource* a_depthRessource)
{
	a_swapChain->CastVulkan()->GetSwapChainFrameBuffers().resize(a_swapChain->CastVulkan()->GetSwapChainImageViews().size());

	for (size_t i = 0; i < a_swapChain->CastVulkan()->GetSwapChainImageViews().size(); i++)
	{
		std::array<VkImageView, 2> l_attachments = {
			a_swapChain->CastVulkan()->GetSwapChainImageViews()[i],
			a_depthRessource->CastVulkan()->GetDepthImageView()
		};

		VkFramebufferCreateInfo l_framebufferCreateInfo = {};
		l_framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		l_framebufferCreateInfo.renderPass = a_renderPass->CastVulkan()->GetInstance();
		l_framebufferCreateInfo.attachmentCount = static_cast<uint32_t>(l_attachments.size());
		l_framebufferCreateInfo.pAttachments = l_attachments.data();
		l_framebufferCreateInfo.width = a_swapChain->CastVulkan()->GetSwapChainExtent().width;
		l_framebufferCreateInfo.height = a_swapChain->CastVulkan()->GetSwapChainExtent().height;
		l_framebufferCreateInfo.layers = 1;

		VkResult l_result = vkCreateFramebuffer(a_device->CastVulkan()->GetDevice(), &l_framebufferCreateInfo, nullptr, &a_swapChain->CastVulkan()->GetSwapChainFrameBuffers()[i]);

		if (l_result != VK_SUCCESS) {
			throw std::runtime_error("Failed to create framebuffer");
		}
	}
}

void VulkanFrameBuffer::Destroy()
{
}
