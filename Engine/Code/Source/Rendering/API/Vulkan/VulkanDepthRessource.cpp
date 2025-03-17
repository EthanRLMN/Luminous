#include "Rendering/API/Vulkan/VulkanDepthRessource.hpp"


void VulkanDepthRessource::Create(IDevice* a_device, ISwapChain* a_swapChain,IRenderPass* a_renderPass)
{
	
	VkFormat l_depthFormat = a_renderPass->CastVulkan()->FindDepthFormat(a_device->CastVulkan()->GetPhysicalDevice());

	CreateImage(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(),  a_swapChain->CastVulkan()->swapChainExtent.width, a_swapChain->CastVulkan()->swapChainExtent.height, l_depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_depthImage, m_depthImageMemory);
	m_depthImageView = a_swapChain->CastVulkan()->CreateImageView(m_depthImage, a_device->CastVulkan()->GetDevice(), l_depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
}

void VulkanDepthRessource::Destroy()
{
}


void VulkanDepthRessource::CreateImage(VkDevice a_device, VkPhysicalDevice a_physicalDevice, uint32_t a_width, uint32_t a_height, VkFormat a_format, VkImageTiling a_tiling, VkImageUsageFlags a_usage, VkMemoryPropertyFlags a_properties, VkImage& a_image, VkDeviceMemory& a_imageMemory)
{
	VkImageCreateInfo l_imageInfo{};
	l_imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
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
	l_imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	l_imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;


	if (vkCreateImage(a_device, &l_imageInfo, nullptr, &a_image) != VK_SUCCESS)
	{
		std::cout << "Failed to create Image";
	}

	VkMemoryRequirements l_memoryRequirement;
	vkGetImageMemoryRequirements(a_device, a_image, &l_memoryRequirement);

	VkMemoryAllocateInfo l_allocateInfo{};
	l_allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	l_allocateInfo.allocationSize = l_memoryRequirement.size;
	l_allocateInfo.memoryTypeIndex = FindMemoryType(a_physicalDevice, l_memoryRequirement.memoryTypeBits, a_properties);

	if (vkAllocateMemory(a_device, &l_allocateInfo, nullptr, &a_imageMemory) != VK_SUCCESS) {
		std::cout << "failed to allocate image memory";
	}

	vkBindImageMemory(a_device, a_image, a_imageMemory, 0);
}

uint32_t VulkanDepthRessource::FindMemoryType(VkPhysicalDevice a_physicalDevice, uint32_t a_typeFilter, VkMemoryPropertyFlags a_properties)
{
	VkPhysicalDeviceMemoryProperties l_memoryProperties;
	vkGetPhysicalDeviceMemoryProperties(a_physicalDevice, &l_memoryProperties);

	for (uint32_t i = 0; i < l_memoryProperties.memoryTypeCount; ++i) {
		if ((a_typeFilter & (1 << i)) && (l_memoryProperties.memoryTypes[i].propertyFlags & a_properties)) {
			return i;
		}
	}
	std::cout << " failed to find suitable memory type";
	return 0;
}

VkImage VulkanDepthRessource::GetDepthImage() const
{
	return m_depthImage;
}

VkDeviceMemory VulkanDepthRessource::GetDepthImageMemory() const
{
	return m_depthImageMemory;
}

VkImageView VulkanDepthRessource::GetDepthImageView() const
{
	return m_depthImageView;
}
