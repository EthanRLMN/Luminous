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

	VkSwapchainKHR m_swapChain{ nullptr };

	VkFormat m_swapChainImageFormat = VK_FORMAT_UNDEFINED;
	VkExtent2D m_swapChainExtent = { 0, 0 };

	std::vector<VkImage> m_swapChainImages{ nullptr };
	std::vector<VkImageView> m_swapChainImageViews{ nullptr };
};