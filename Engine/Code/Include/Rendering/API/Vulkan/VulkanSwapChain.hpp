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


	[[nodiscard]] VkSwapchainKHR GetSwapChain() const { return m_swapChain; }

	[[nodiscard]] VkFormat GetSwapChainImageFormat() const { return swapChainImageFormat; }
	[[nodiscard]] VkExtent2D GetSwapChainExtent() const { return swapChainExtent; }

	[[nodiscard]] std::vector < VkImage> GetSwapChainImages() const { return swapChainImages; }
	[[nodiscard]] std::vector < VkFramebuffer> GetSwapChainFrameBuffers() const { return swapChainFrameBuffers; }
	[[nodiscard]] std::vector < VkCommandBuffer> GetCommandBuffers() const { return commandBuffers; }
	[[nodiscard]] std::vector < VkImageView> GetSwapChainImageViews() const { return swapChainImageViews; }

	VkImageView CreateImageView(VkImage a_image, VkDevice a_device, VkFormat a_format, VkImageAspectFlags a_aspectFlags);
private:
	SwapChainDetails GetSwapChainDetails(VkPhysicalDevice a_device, VkSurfaceKHR a_surface);
	QueueFamilyIndices GetQueueFamilies(VkPhysicalDevice a_device, VkSurfaceKHR a_surface);
	VkSurfaceFormatKHR ChooseBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& a_formats);
	VkPresentModeKHR ChooseBestPresentationMode(const std::vector<VkPresentModeKHR> a_presentationModes);
	VkExtent2D ChooseSwapExtend(const VkSurfaceCapabilitiesKHR& a_surfaceCapabilities, GLFWwindow* a_window);

	VkSwapchainKHR m_swapChain{ VK_NULL_HANDLE };

	VkFormat swapChainImageFormat = VK_FORMAT_UNDEFINED;
	VkExtent2D swapChainExtent = { 0, 0 };

	std::vector<VkImage> swapChainImages{ VK_NULL_HANDLE };
	std::vector<VkFramebuffer> swapChainFrameBuffers{ VK_NULL_HANDLE };
	std::vector<VkCommandBuffer> commandBuffers{ VK_NULL_HANDLE };
	std::vector<VkImageView> swapChainImageViews{ VK_NULL_HANDLE };
};