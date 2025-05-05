#include "Rendering/Vulkan/VulkanFrameBuffer.hpp"
#include "Rendering/Vulkan/VulkanDepthResource.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanMultiSampling.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"

void VulkanFrameBuffer::Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass, IDepthResource* a_depthResource, IMultiSampling* a_multiSampling, const bool& a_isEditor)
{
    SetFrameBuffersSize(a_swapChain->CastVulkan()->GetSwapChainImageViews().size());
    const VulkanSwapChain* l_vulkanSwapChain = a_swapChain->CastVulkan();

    for (size_t i = 0; i < l_vulkanSwapChain->GetSwapChainImageViews().size(); ++i)
    {
        std::vector<VkImageView> l_attachments{};
        if (!a_isEditor)
            l_attachments = { a_multiSampling->CastVulkan()->GetColorImageView(), a_depthResource->CastVulkan()->GetDepthImageView(), l_vulkanSwapChain->GetSwapChainImageViews()[i] };
        else
            l_attachments = { l_vulkanSwapChain->GetSwapChainImageViews()[i] };

        VkFramebufferCreateInfo l_framebufferCreateInfo = { VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO };
        l_framebufferCreateInfo.renderPass = a_renderPass->CastVulkan()->GetRenderPass();
        l_framebufferCreateInfo.attachmentCount = static_cast<uint32_t>(l_attachments.size());
        l_framebufferCreateInfo.pAttachments = l_attachments.data();
        l_framebufferCreateInfo.width = l_vulkanSwapChain->GetSwapChainExtent().width;
        l_framebufferCreateInfo.height = l_vulkanSwapChain->GetSwapChainExtent().height;
        l_framebufferCreateInfo.layers = 1;

        const VkResult l_result = vkCreateFramebuffer(a_device->CastVulkan()->GetDevice(), &l_framebufferCreateInfo, nullptr, &m_frameBuffers[i]);;
        if (l_result != VK_SUCCESS)
            throw std::runtime_error("Failed to create framebuffer");
    }
    DEBUG_LOG_INFO("Vulkan FrameBuffer : Create FrameBuffer!\n");
}


void VulkanFrameBuffer::Destroy(IDevice* a_device)
{
    for (const VkFramebuffer& l_frameBuffer : m_frameBuffers)
        vkDestroyFramebuffer(a_device->CastVulkan()->GetDevice(), l_frameBuffer, nullptr);

    DEBUG_LOG_INFO("Vulkan FrameBuffer : Create FrameBuffer!\n");
}
