#pragma once

#include <string>
#include <vulkan/vulkan.h>

#include "ITexture.hpp"

class VulkanTexture final : public ITexture
{
public:
    bool Create(IResourceManager* a_manager, IResourceParams a_params) override;
    void Destroy(IDevice* a_device) override;


	void CreateTextureImage(IDevice* a_device, ISwapChain* a_swapChain, IDepthResource* a_depthResource, ICommandPool* a_commandPool, std::string a_path);

	void CreateTextureImageView(IDevice* a_device, ISwapChain* a_swapChain);
	void CreateTextureSampler(IDevice* a_device);

	void CreateBuffer(VkDevice a_device, VkPhysicalDevice _physicalDevice, VkDeviceSize a_size,
	                  VkBufferUsageFlags a_usage, VkMemoryPropertyFlags a_properties, VkBuffer& a_buffer,
	                  VkDeviceMemory& a_bufferMemory, IDepthResource* a_depthResource);

	void TransitionImageLayout(VkDevice a_device, VkQueue a_graphicsQueue, VkCommandPool a_commandPool, VkImage a_image,
	                           VkFormat a_format, VkImageLayout a_oldLayout, VkImageLayout a_newLayout);

	VkCommandBuffer BeginSingleTimeCommands(VkDevice a_device, VkCommandPool a_commandPool);

	void EndSingleTimeCommands(VkDevice a_device, VkQueue a_graphicsQueue, VkCommandPool a_commandPool,
	                           VkCommandBuffer a_commandBuffer);

	void CopyBufferToImage(VkDevice a_device, VkQueue a_graphicsQueue, VkCommandPool a_commandPool, VkBuffer a_buffer,
	                       VkImage a_image, uint32_t a_width, uint32_t a_height);


	VulkanTexture* CastVulkan() override { return this; }


	[[nodiscard]] VkImage GetTextureImage() const;
	[[nodiscard]] VkDeviceMemory GetTextureImageMemory() const;
	[[nodiscard]] VkImageView GetTextureImageView() const;
	[[nodiscard]] VkSampler GetTextureSampler() const;

private:
	VkImage m_textureImage{nullptr};
	VkImageView m_textureImageView{nullptr};
	VkDeviceMemory m_textureImageMemory{nullptr};
	VkSampler m_textureSampler{nullptr};
};

