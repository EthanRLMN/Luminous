#include "Rendering/API/Vulkan/VulkanTexture.hpp"

#define STB_IMAGE_IMPLEMENTATION

void VulkanTexture::Create(IDevice* a_device, ISwapChain* a_swapChain, IDepthRessource* a_depthRessource, ICommandPool* a_commandPool)
{
	//CreateTextureImage(a_device,a_depthRessource,a_commandPool);
	//CreateTextureImageView(a_device,a_swapChain);
	//CreateTextureSampler(a_device);
}

void VulkanTexture::Destroy()
{
}

void VulkanTexture::CreateTextureImage(IDevice* a_device, IDepthRessource* a_depthRessource, ICommandPool* a_commandPool)
{
	/*
	int l_texWidth, l_texHeight, l_texChannels;
	//stb_image
	stbi_uc* l_pixels = stbi_load(TEXTURE_PATH.c_str(), &l_texWidth, &l_texHeight, &l_texChannels, STBI_rgb_alpha);
	VkDeviceSize l_imageSize = l_texWidth * l_texHeight * 4;

	if (!l_pixels) {
		std::cout << ("failed to load texture image");
	}

	VkBuffer l_stagingBuffer;
	VkDeviceMemory l_stagingBufferMemory;
	CreateBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), l_imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, l_stagingBuffer, l_stagingBufferMemory, a_depthRessource);

	void* l_data;
	vkMapMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory, 0, l_imageSize, 0, &l_data);
	memcpy(l_data, l_pixels, static_cast<size_t>(l_imageSize));
	vkUnmapMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory);

	stbi_image_free(l_pixels);

	a_depthRessource->CastVulkan()->CreateImage(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), l_texWidth, l_texHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_textureImage, m_textureImageMemory);

	TransitionImageLayout(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetGraphicsQueue(), a_commandPool->CastVulkan()->GetCommandPool(), m_textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	CopyBufferToImage(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetGraphicsQueue(), a_commandPool->CastVulkan()->GetCommandPool(), l_stagingBuffer, m_textureImage, static_cast<uint32_t>(l_texWidth), static_cast<uint32_t>(l_texHeight));
	TransitionImageLayout(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetGraphicsQueue(), a_commandPool->CastVulkan()->GetCommandPool(), m_textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	vkDestroyBuffer(a_device->CastVulkan()->GetDevice(), l_stagingBuffer, nullptr);
	vkFreeMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory, nullptr);*/
}



void VulkanTexture::CreateTextureImageView(IDevice* a_device,ISwapChain* a_swapChain)
{
	m_textureImageView = a_swapChain->CastVulkan()->CreateImageView(m_textureImage, a_device->CastVulkan()->GetDevice(), VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
}

void VulkanTexture::CreateTextureSampler(IDevice* a_device)
{
	VkPhysicalDeviceProperties l_properties{};
	vkGetPhysicalDeviceProperties(a_device->CastVulkan()->GetPhysicalDevice(), &l_properties);

	VkSamplerCreateInfo l_samplerInfo{};
	l_samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	l_samplerInfo.magFilter = VK_FILTER_LINEAR;
	l_samplerInfo.minFilter = VK_FILTER_LINEAR;
	l_samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	l_samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	l_samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	l_samplerInfo.anisotropyEnable = VK_TRUE;
	l_samplerInfo.maxAnisotropy = l_properties.limits.maxSamplerAnisotropy;
	l_samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	l_samplerInfo.unnormalizedCoordinates = VK_FALSE;
	l_samplerInfo.compareEnable = VK_FALSE;
	l_samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
	l_samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

	if (vkCreateSampler(a_device->CastVulkan()->GetDevice(), &l_samplerInfo, nullptr, &m_textureSampler) != VK_SUCCESS) {
		std::cout << "Failed to create Texture Sampler";
	}
}


void VulkanTexture::CreateBuffer(VkDevice a_device, VkPhysicalDevice _physicalDevice, VkDeviceSize a_size, VkBufferUsageFlags a_usage, VkMemoryPropertyFlags a_properties, VkBuffer& a_buffer, VkDeviceMemory& a_bufferMemory, IDepthRessource* a_depthRessource)
{
	VkBufferCreateInfo l_bufferInfo{};
	l_bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	l_bufferInfo.size = a_size;
	l_bufferInfo.usage = a_usage;
	l_bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(a_device, &l_bufferInfo, nullptr, &a_buffer) != VK_SUCCESS) {
		std::cout << "Failed to load Buffer";
	}

	VkMemoryRequirements l_memoryRequirements;
	vkGetBufferMemoryRequirements(a_device, a_buffer, &l_memoryRequirements);

	VkMemoryAllocateInfo l_allocateInfo{};
	l_allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	l_allocateInfo.allocationSize = l_memoryRequirements.size;
	l_allocateInfo.memoryTypeIndex = a_depthRessource->CastVulkan()->FindMemoryType(_physicalDevice, l_memoryRequirements.memoryTypeBits, a_properties);

	if (vkAllocateMemory(a_device, &l_allocateInfo, nullptr, &a_bufferMemory) != VK_SUCCESS) {
		std::cout << "Failed to allocateBuffer memory";
	}

	vkBindBufferMemory(a_device, a_buffer, a_bufferMemory, 0);
}

void VulkanTexture::TransitionImageLayout(VkDevice a_device, VkQueue a_graphicsQueue, VkCommandPool a_commandPool, VkImage a_image, VkFormat a_format, VkImageLayout a_oldLayout, VkImageLayout a_newLayout)
{
	VkCommandBuffer l_commandBuffer = BeginSingleTimeCommands(a_device, a_commandPool);

	VkImageMemoryBarrier l_barrier{};

	l_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	l_barrier.oldLayout = a_oldLayout;
	l_barrier.newLayout = a_newLayout;
	l_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	l_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	l_barrier.image = a_image;
	l_barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	l_barrier.subresourceRange.baseMipLevel = 0;
	l_barrier.subresourceRange.levelCount = 1;
	l_barrier.subresourceRange.baseArrayLayer = 0;
	l_barrier.subresourceRange.layerCount = 1;

	VkPipelineStageFlags l_sourceStage;
	VkPipelineStageFlags l_destinationStage;

	if (a_oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && a_newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
		l_barrier.srcAccessMask = 0;
		l_barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

		l_sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		l_destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	}
	else if (a_oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && a_newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
		l_barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		l_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		l_sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		l_destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	}
	else {
		throw std::invalid_argument("Unsupported layout transition");
	}

	vkCmdPipelineBarrier(l_commandBuffer, l_sourceStage, l_destinationStage, 0, 0, nullptr, 0, nullptr, 1, &l_barrier);
	EndSingleTimeCommands(a_device, a_graphicsQueue, a_commandPool, l_commandBuffer);
}


VkCommandBuffer VulkanTexture::BeginSingleTimeCommands(VkDevice a_device, VkCommandPool a_commandPool)
{
	VkCommandBufferAllocateInfo l_allocateInfo{};
	l_allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	l_allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	l_allocateInfo.commandPool = a_commandPool;
	l_allocateInfo.commandBufferCount = 1;

	VkCommandBuffer l_commandBuffer;


	if (a_commandPool == VK_NULL_HANDLE) {
		std::cerr << "Erreur : commandPool est invalide" << std::endl;
		return VK_NULL_HANDLE;
	}

	VkResult result = vkAllocateCommandBuffers(a_device, &l_allocateInfo, &l_commandBuffer);
	if (result != VK_SUCCESS) {
		std::cerr << "Erreur vkAllocateCommandBuffers: " << result << std::endl;
		return VK_NULL_HANDLE;
	}

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(l_commandBuffer, &beginInfo);
	return l_commandBuffer;
}

void VulkanTexture::EndSingleTimeCommands(VkDevice a_device, VkQueue a_graphicsQueue, VkCommandPool a_commandPool, VkCommandBuffer a_commandBuffer)
{
	vkEndCommandBuffer(a_commandBuffer);

	VkSubmitInfo l_submitInfo{};
	l_submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	l_submitInfo.commandBufferCount = 1;
	l_submitInfo.pCommandBuffers = &a_commandBuffer;

	vkQueueSubmit(a_graphicsQueue, 1, &l_submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(a_graphicsQueue);

	vkFreeCommandBuffers(a_device, a_commandPool, 1, &a_commandBuffer);
}

void VulkanTexture::CopyBufferToImage(VkDevice a_device, VkQueue a_graphicsQueue, VkCommandPool a_commandPool, VkBuffer a_buffer, VkImage a_image, uint32_t a_width, uint32_t a_height) {

	VkCommandBuffer l_commandBuffer = BeginSingleTimeCommands(a_device, a_commandPool);

	VkBufferImageCopy l_bufferImageCopy{};

	l_bufferImageCopy.bufferOffset = 0;
	l_bufferImageCopy.bufferRowLength = 0;
	l_bufferImageCopy.bufferImageHeight = 0;
	l_bufferImageCopy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	l_bufferImageCopy.imageSubresource.mipLevel = 0;
	l_bufferImageCopy.imageSubresource.baseArrayLayer = 0;
	l_bufferImageCopy.imageSubresource.layerCount = 1;
	l_bufferImageCopy.imageOffset = { 0,0,0 };
	l_bufferImageCopy.imageExtent = { a_width,a_height,1 };

	vkCmdCopyBufferToImage(l_commandBuffer, a_buffer, a_image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &l_bufferImageCopy);
	EndSingleTimeCommands(a_device, a_graphicsQueue, a_commandPool, l_commandBuffer);
}

VkImage VulkanTexture::GetTextureImage() const
{
	return m_textureImage;
}

VkDeviceMemory VulkanTexture::GetTextureImageMemory() const
{
	return m_textureImageMemory;
}

VkImageView VulkanTexture::GetTextureImageView() const
{
	return m_textureImageView;
}

VkSampler VulkanTexture::GetTextureSampler() const
{
	return m_textureSampler;
}
