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


void VulkanDepthResource::CreateImage(const VkDevice a_device, const VkPhysicalDevice a_physicalDevice, const uint32_t a_width, const uint32_t a_height, const VkFormat a_format, const VkImageTiling a_tiling, const VkImageUsageFlags a_usage, const VkMemoryPropertyFlags a_properties, VkImage& a_image, VkDeviceMemory& a_imageMemory, const VkSampleCountFlagBits a_numSamples)
{
    FillImageInfo(a_device, a_width, a_height, a_format, a_tiling, a_usage, a_image, VK_SAMPLE_COUNT_1_BIT);

	VkMemoryRequirements l_memoryRequirement { };
	vkGetImageMemoryRequirements(a_device, a_image, &l_memoryRequirement);

	VkMemoryAllocateInfo l_allocateInfo { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
	l_allocateInfo.allocationSize = l_memoryRequirement.size;
	l_allocateInfo.memoryTypeIndex = FindMemoryType(a_physicalDevice, l_memoryRequirement.memoryTypeBits, a_properties);

	if (vkAllocateMemory(a_device, &l_allocateInfo, nullptr, &a_imageMemory) != VK_SUCCESS)
		DEBUG_LOG_ERROR("Vulkan DepthResource : Failed to allocated image memory!\n");

	vkBindImageMemory(a_device, a_image, a_imageMemory, 0);
}


uint32_t VulkanDepthResource::FindMemoryType(const VkPhysicalDevice a_physicalDevice, const uint32_t a_typeFilter, const VkMemoryPropertyFlags a_properties)
{
	VkPhysicalDeviceMemoryProperties l_memoryProperties { };
	vkGetPhysicalDeviceMemoryProperties(a_physicalDevice, &l_memoryProperties);

	for (uint32_t i = 0; i < l_memoryProperties.memoryTypeCount; ++i)
		if (a_typeFilter & 1 << i && l_memoryProperties.memoryTypes[i].propertyFlags & a_properties)
			return i;

	DEBUG_LOG_ERROR("Vulkan DepthResource : Failed to find a suitable memory type!\n");
	return 0;
}


void VulkanDepthResource::FillImageInfo(const VkDevice a_device, const uint32_t a_width, const uint32_t a_height, const VkFormat a_format, const VkImageTiling a_tiling, const VkImageUsageFlags a_usage, VkImage& a_image, const VkSampleCountFlagBits a_numSamples)
{
	VkImageCreateInfo l_imageInfo { VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };
	l_imageInfo.imageType = VK_IMAGE_TYPE_2D;
	l_imageInfo.extent.width = a_width;
	l_imageInfo.extent.height = a_height;
	l_imageInfo.extent.depth = 1;
	l_imageInfo.mipLevels = 1;
	l_imageInfo.arrayLayers = 1;
	l_imageInfo.format = a_format;
	l_imageInfo.tiling = a_tiling;
	l_imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	l_imageInfo.usage = a_usage;
	l_imageInfo.samples = a_numSamples;
	l_imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateImage(a_device, &l_imageInfo, nullptr, &a_image) != VK_SUCCESS)
		DEBUG_LOG_ERROR("Vulkan DepthResource : Failed to create Image!\n");
}