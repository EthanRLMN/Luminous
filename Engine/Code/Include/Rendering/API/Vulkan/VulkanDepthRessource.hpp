#pragma once
#include <vulkan/vulkan.h>

#include "IDepthRessource.hpp"
#include <Rendering/API/Vulkan/VulkanDevice.hpp>
#include <Rendering/API/Vulkan/VulkanSwapChain.hpp>
#include <Rendering/API/Vulkan/VulkanRenderPass.hpp>

#include "Struct/VulkanUtilities.hpp"
#include "Utilities.hpp"



class VulkanDepthRessource : public IDepthRessource
{
public:
	void Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass) override;
	void Destroy() override;

	void CreateImage(VkDevice a_device, VkPhysicalDevice a_physicalDevice, uint32_t a_width, uint32_t a_height, VkFormat a_format, VkImageTiling a_tiling, VkImageUsageFlags a_usage, VkMemoryPropertyFlags a_properties, VkImage& a_image, VkDeviceMemory& a_imageMemory);

	uint32_t FindMemoryType(VkPhysicalDevice a_physicalDevice, uint32_t a_typeFilter, VkMemoryPropertyFlags a_properties);

	[[nodiscard]] virtual VkImage GetDepthImage() const;
	[[nodiscard]] virtual VkDeviceMemory GetDepthImageMemory() const;
	[[nodiscard]] virtual VkImageView GetDepthImageView() const;

private:
	VkImage m_depthImage{ VK_NULL_HANDLE };
	VkDeviceMemory m_depthImageMemory{ VK_NULL_HANDLE };
	VkImageView m_depthImageView{ VK_NULL_HANDLE };
};
