#include "IDevice.hpp"
#include "IRenderPass.hpp"
#include "ISwapChain.hpp"

#include "Rendering/Vulkan/VulkanDepthResource.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"


void VulkanDepthResource::Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass)
{
    const VkFormat l_depthFormat = a_renderPass->CastVulkan()->FindDepthFormat(a_device->CastVulkan()->GetPhysicalDevice());
    CreateImage(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), a_swapChain->CastVulkan()->GetSwapChainExtent().width, a_swapChain->CastVulkan()->GetSwapChainExtent().height, l_depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_depthImage, m_depthImageMemory);

	a_swapChain->CastVulkan()->CreateImage(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), a_swapChain->CastVulkan()->GetSwapChainExtent().width, a_swapChain->CastVulkan()->GetSwapChainExtent().height, l_depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_depthImage, m_depthImageMemory, a_device->CastVulkan()->GetMSAASamples());

	m_depthImageView = a_swapChain->CastVulkan()->CreateImageView(m_depthImage, a_device->CastVulkan()->GetDevice(), l_depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
	DEBUG_LOG_INFO("Vulkan DepthResource : DepthResource Created!\n");
}


void VulkanDepthResource::Destroy(IDevice* a_device)
{
    vkFreeMemory(a_device->CastVulkan()->GetDevice(), m_depthImageMemory, nullptr);
    vkDestroyImage(a_device->CastVulkan()->GetDevice(), m_depthImage, nullptr);
    vkDestroyImageView(a_device->CastVulkan()->GetDevice(), m_depthImageView, nullptr);

    DEBUG_LOG_INFO("Vulkan DepthResource : DepthResource Destroyed!\n");
}


