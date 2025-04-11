#pragma once

#include <vector>
#include <GLFW/glfw3.h>

#include "ISwapChain.hpp"

#include "Utils/QueueFamilyIndiceUtils.hpp"

#include "Struct/VulkanUtilities.hpp"

#include "VulkanSurface.hpp"

class VulkanSwapChain final : public ISwapChain
{
public:

	void Create(IWindow* a_window, IDevice* a_device, ISurface* a_surface) override;
	void Destroy(IDevice* a_device) override;

	VulkanSwapChain* CastVulkan() override { return this; }

	void CreateImage(VkDevice a_device, VkPhysicalDevice a_physicalDevice, uint32_t a_width, uint32_t a_height, VkFormat a_format, VkImageTiling a_tiling, VkImageUsageFlags a_usage, VkMemoryPropertyFlags a_properties, VkImage& a_image, VkDeviceMemory& a_imageMemory, const VkSampleCountFlagBits a_numSamples);

	uint32_t FindMemoryType(VkPhysicalDevice a_physicalDevice, uint32_t a_typeFilter, VkMemoryPropertyFlags a_properties);

	[[nodiscard]] VkSwapchainKHR GetSwapChain() const { return m_swapChain; }

	[[nodiscard]] VkFormat GetSwapChainImageFormat() const { return m_swapChainImageFormat; }
	[[nodiscard]] VkExtent2D GetSwapChainExtent() const { return m_swapChainExtent; }

	[[nodiscard]] std::vector < VkImage> GetSwapChainImages() const { return m_swapChainImages; }
	[[nodiscard]] std::vector < VkImageView> GetSwapChainImageViews() const { return m_swapChainImageViews; }
	

	VkImageView CreateImageView(VkImage a_image, VkDevice a_device, VkFormat a_format, VkImageAspectFlags a_aspectFlags);

private:
	SwapChainDetails GetSwapChainDetails(VkPhysicalDevice a_device, VkSurfaceKHR a_surface);
	QueueFamilyIndices GetQueueFamilies(VkPhysicalDevice a_device, VkSurfaceKHR a_surface);
	VkSurfaceFormatKHR ChooseBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& a_formats);
	VkPresentModeKHR ChooseBestPresentationMode(const std::vector<VkPresentModeKHR>& a_presentationModes);
	VkExtent2D ChooseSwapExtend(const VkSurfaceCapabilitiesKHR& a_surfaceCapabilities, GLFWwindow* a_window);

	void FillImageInfo(VkDevice a_device, uint32_t a_width, uint32_t a_height, VkFormat a_format, VkImageTiling a_tiling, VkImageUsageFlags a_usage, VkImage& a_image, const VkSampleCountFlagBits a_numSamples);

	VkSwapchainKHR m_swapChain{ nullptr };

	VkFormat m_swapChainImageFormat = VK_FORMAT_UNDEFINED;
	VkExtent2D m_swapChainExtent = { 0, 0 };

	std::vector<VkImage> m_swapChainImages{ nullptr };
	std::vector<VkImageView> m_swapChainImageViews{ nullptr };
};