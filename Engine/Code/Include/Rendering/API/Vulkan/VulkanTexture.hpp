#pragma once
#include "ITexture.hpp"

#include <vulkan/vulkan.hpp>
#include <string>
#include "../../assimp/contrib/stb/stb_image.h"


#include "Rendering/API/Vulkan/VulkanDevice.hpp"
#include "Rendering/API/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/API/Vulkan/VulkanDepthRessource.hpp"
#include "Rendering/API/Vulkan/VulkanCommandPool.hpp"



class VulkanTexture : public ITexture
{
public:
	
	void Create(IDevice* a_device, ISwapChain* a_swapChain, IDepthRessource* a_depthRessource, ICommandPool* a_commandPool) override;
	void Destroy()override;

	void CreateTextureImage(IDevice* a_device, IDepthRessource* a_depthRessource,ICommandPool* a_commandPool);

	void CreateTextureImageView(IDevice* a_device, ISwapChain* a_swapChain);
	void CreateTextureSampler(IDevice* a_device);

	void CreateBuffer(VkDevice a_device, VkPhysicalDevice _physicalDevice, VkDeviceSize a_size, VkBufferUsageFlags a_usage, VkMemoryPropertyFlags a_properties, VkBuffer& a_buffer, VkDeviceMemory& a_bufferMemory, IDepthRessource* a_depthRessource);

	void TransitionImageLayout(VkDevice a_device, VkQueue a_graphicsQueue, VkCommandPool a_commandPool, VkImage a_image, VkFormat a_format, VkImageLayout a_oldLayout, VkImageLayout a_newLayout);

	VkCommandBuffer BeginSingleTimeCommands(VkDevice a_device, VkCommandPool a_commandPool);

	void EndSingleTimeCommands(VkDevice a_device, VkQueue a_graphicsQueue, VkCommandPool a_commandPool, VkCommandBuffer a_commandBuffer);

	void CopyBufferToImage(VkDevice a_device, VkQueue a_graphicsQueue, VkCommandPool a_commandPool, VkBuffer a_buffer, VkImage a_image, uint32_t a_width, uint32_t a_height);


	const std::string TEXTURE_PATH{ "C:/Users/sheni/Documents/Code/2024_gp_2028_gp_2028_projet_moteur-luminousengine/Engine/Assets/Textures/Untitled312.png" };

	[[nodiscard]] VkImage GetTextureImage() const;
	[[nodiscard]] VkDeviceMemory GetTextureImageMemory() const;
	[[nodiscard]] VkImageView GetTextureImageView() const;
	[[nodiscard]] VkSampler GetTextureSampler() const;


private:
	VkImage m_textureImage{ VK_NULL_HANDLE };
	VkDeviceMemory m_textureImageMemory{ VK_NULL_HANDLE };
	VkImageView m_textureImageView{ VK_NULL_HANDLE };
	VkSampler m_textureSampler{ VK_NULL_HANDLE };

};

