#pragma once

#include "ISwapChain.hpp"
#include "VulkanSurface.hpp"
#include <GLFW/glfw3.h>
#include <vector>
#include "Struct/VulkanUtilities.hpp"
#include "Utilities.hpp"


class VulkanSwapChain : public ISwapChain
{
public:
	void Create(IWindow* a_window, IDevice* a_device, ISurface* a_surface) override;

	void Destroy(IDevice* a_device) override;

	VulkanSwapChain* CastVulkan() override { return this; }

	VkSwapchainKHR m_swapchain{ VK_NULL_HANDLE };

	std::vector<VkImage> swapChainImages{ VK_NULL_HANDLE };
	std::vector<VkFramebuffer> swapChainFrameBuffers{ VK_NULL_HANDLE };
	std::vector<VkCommandBuffer> commandBuffers{ VK_NULL_HANDLE };
	std::vector<VkImageView> swapChainImageViews{ VK_NULL_HANDLE };

	VkFormat swapChainImageFormat = VK_FORMAT_UNDEFINED;
	VkExtent2D swapChainExtent = { 0, 0 };

	[[nodiscard]] VkFormat GetSwapChainImageFormat() const;
	[[nodiscard]] VkExtent2D GetSwapChainExtent() const;

	VkImageView CreateImageView(VkImage a_image, VkDevice a_device, VkFormat a_format, VkImageAspectFlags a_aspectFlags);
private:
	SwapChainDetails GetSwapChainDetails(VkPhysicalDevice a_device, VkSurfaceKHR a_surface);

	QueueFamilyIndices GetQueueFamilies(VkPhysicalDevice a_device, VkSurfaceKHR a_surface);

	VkSurfaceFormatKHR ChooseBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& a_formats);

	VkPresentModeKHR ChooseBestPresentationMode(const std::vector<VkPresentModeKHR> a_presentationModes);

	VkExtent2D ChooseSwapExtend(const VkSurfaceCapabilitiesKHR& a_surfaceCapabilities, GLFWwindow* a_window);


};