#pragma once
#include <vector>
#include <GLFW/glfw3.h>

#include "ISwapChain.hpp"
#include "Struct/VulkanUtilities.hpp"
#include "Utils/QueueFamilyIndiceUtils.hpp"

class VulkanSwapChain final : public ISwapChain
{
public:
	void Create(IWindow* a_window, IDevice* a_device, ISurface* a_surface) override;
	void Destroy(IDevice* a_device) override;
	VulkanSwapChain* CastVulkan() override { return this; }

    static uint32_t FindMemoryType(const VkPhysicalDevice& a_physicalDevice, const uint32_t& a_typeFilter, const VkMemoryPropertyFlags& a_properties);
    static void CreateImage(const VkDevice& a_device, const VkPhysicalDevice& a_physicalDevice, const uint32_t& a_width, const uint32_t& a_height, const VkFormat& a_format, const VkImageTiling& a_tiling, const VkImageUsageFlags& a_usage, const VkMemoryPropertyFlags& a_properties, VkImage& a_image, VkDeviceMemory& a_imageMemory, VkSampleCountFlagBits a_numSamples, uint32_t a_mipLevels);
    static VkImageView CreateImageView(const VkImage& a_image, const VkDevice& a_device, const VkFormat& a_format, const VkImageAspectFlags& a_aspectFlags, uint32_t a_mipLevels);

	[[nodiscard]] VkSwapchainKHR GetSwapChain() const { return m_swapChain; }
	[[nodiscard]] VkFormat GetSwapChainImageFormat() const { return m_swapChainImageFormat; }
	[[nodiscard]] VkExtent2D GetSwapChainExtent() const { return m_swapChainExtent; }
	[[nodiscard]] std::vector<VkImage> GetSwapChainImages() const { return m_swapChainImages; }
	[[nodiscard]] std::vector<VkImageView> GetSwapChainImageViews() const { return m_swapChainImageViews; }
    [[nodiscard]] uint32_t GetMipLevel() const { return m_mipLevels; }


private:
    static SwapChainDetails GetSwapChainDetails(const VkPhysicalDevice& a_device, const VkSurfaceKHR& a_surface);
    static QueueFamilyIndices GetQueueFamilies(const VkPhysicalDevice& a_device, const VkSurfaceKHR& a_surface);
    static VkSurfaceFormatKHR ChooseBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& a_formats);
    static VkPresentModeKHR ChooseBestPresentationMode(const std::vector<VkPresentModeKHR>& a_presentationModes);
    static VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& a_surfaceCapabilities, GLFWwindow* a_window);

    static void FillSwapChainCreationInfo(VkSwapchainCreateInfoKHR& a_swapChainCreateInfo, const VkSurfaceKHR& a_surface, uint32_t a_imageCount, const VkSurfaceFormatKHR& a_surfaceFormat, const VkExtent2D& a_extent);
    static void FillSwapChainGraphicsFamilyData(VkSwapchainCreateInfoKHR& a_swapChainCreateInfo, const QueueFamilyIndices& a_indices, const std::vector<uint32_t>& a_queueFamilyIndices, const SwapChainDetails& a_swapChainDetails, const VkPresentModeKHR& a_presentMode);
    static void FillImageInfo(const VkDevice& a_device, const uint32_t& a_width, const uint32_t& a_height, const VkFormat& a_format, const VkImageTiling& a_tiling, const VkImageUsageFlags& a_usage, VkImage& a_image, VkSampleCountFlagBits a_numSamples, uint32_t a_mipLevels);
    void SendSwapChainData(const VkDevice& a_vkDevice, uint32_t& a_imageCount, const VkSurfaceFormatKHR& a_surfaceFormat, const VkExtent2D& a_extent);

	VkSwapchainKHR m_swapChain{ nullptr };
	VkFormat m_swapChainImageFormat{ VK_FORMAT_UNDEFINED };
	VkExtent2D m_swapChainExtent{ 0, 0 };
	std::vector<VkImage> m_swapChainImages{ nullptr };
	std::vector<VkImageView> m_swapChainImageViews{ nullptr };

    uint32_t m_mipLevels{ 0 };
};