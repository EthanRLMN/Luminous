#include "IWindow.hpp"

#include "Core/GLFW/GLFWWindow.hpp"

#include "Rendering/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"


void VulkanSwapChain::Create(IWindow* a_window, IDevice* a_device, ISurface* a_surface)
{
	const VkPhysicalDevice l_vkPhysDevice = a_device->CastVulkan()->GetPhysicalDevice();
	const VkDevice l_vkDevice = a_device->CastVulkan()->GetDevice();
	const VkSurfaceKHR l_vkSurface = a_surface->CastVulkan()->GetSurface();

	const SwapChainDetails l_swapChainDetails = GetSwapChainDetails(l_vkPhysDevice, l_vkSurface);

	const VkSurfaceFormatKHR l_surfaceFormat = ChooseBestSurfaceFormat(l_swapChainDetails.formats);
	const VkPresentModeKHR l_presentMode = ChooseBestPresentationMode(l_swapChainDetails.presentationModes);
	const VkExtent2D l_extent = ChooseSwapExtend(l_swapChainDetails.surfaceCapabilities, dynamic_cast<GLFWWindow*>(a_window)->GetGLFWWindow());

	uint32_t l_imageCount = l_swapChainDetails.surfaceCapabilities.minImageCount + 1;
	if (l_swapChainDetails.surfaceCapabilities.maxImageCount > 0 && l_swapChainDetails.surfaceCapabilities.maxImageCount < l_imageCount) l_imageCount = l_swapChainDetails.surfaceCapabilities.maxImageCount;

	VkSwapchainCreateInfoKHR l_swapChainCreateInfo = { };
	l_swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	l_swapChainCreateInfo.surface = a_surface->CastVulkan()->GetSurface();
	l_swapChainCreateInfo.minImageCount = l_imageCount;
	l_swapChainCreateInfo.imageFormat = l_surfaceFormat.format;
	l_swapChainCreateInfo.imageColorSpace = l_surfaceFormat.colorSpace;
	l_swapChainCreateInfo.imageExtent = l_extent;
	l_swapChainCreateInfo.imageArrayLayers = 1;
	l_swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	const QueueFamilyIndices l_indices = GetQueueFamilies(l_vkPhysDevice, l_vkSurface);

	const uint32_t l_queueFamilyIndices[] = { static_cast<uint32_t>(l_indices.graphicsFamily), static_cast<uint32_t>(l_indices.presentationFamily) };

	if (l_indices.graphicsFamily != l_indices.presentationFamily)
	{
		l_swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		l_swapChainCreateInfo.queueFamilyIndexCount = 2;
		l_swapChainCreateInfo.pQueueFamilyIndices = l_queueFamilyIndices;
	} else
	{
		l_swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		l_swapChainCreateInfo.queueFamilyIndexCount = 0;
		l_swapChainCreateInfo.pQueueFamilyIndices = nullptr;
	}

	l_swapChainCreateInfo.preTransform = l_swapChainDetails.surfaceCapabilities.currentTransform;
	l_swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	l_swapChainCreateInfo.presentMode = l_presentMode;
	l_swapChainCreateInfo.clipped = VK_TRUE;
	l_swapChainCreateInfo.oldSwapchain = nullptr;

	const VkResult l_result = vkCreateSwapchainKHR(l_vkDevice, &l_swapChainCreateInfo, nullptr, &m_swapChain);

	if (l_result != VK_SUCCESS)
		DEBUG_LOG_ERROR("Failed to create a SwapChain\n");

	vkGetSwapchainImagesKHR(l_vkDevice, m_swapChain, &l_imageCount, nullptr);
	m_swapChainImages.resize(l_imageCount);

	vkGetSwapchainImagesKHR(l_vkDevice, m_swapChain, &l_imageCount, m_swapChainImages.data());
	m_swapChainImageFormat = l_surfaceFormat.format;
	m_swapChainExtent = l_extent;

	m_swapChainImageViews.resize(m_swapChainImages.size());

	for (uint32_t i { 0 }; i < m_swapChainImages.size(); ++i)
		m_swapChainImageViews[i] = CreateImageView(m_swapChainImages[i], l_vkDevice, m_swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT);

	DEBUG_LOG_INFO("Vulkan SwapChain : SwapChain created!\n");
}


void VulkanSwapChain::Destroy(IDevice* a_device)
{
	for (size_t i { 0 }; i < m_swapChainImageViews.size(); ++i)
		vkDestroyImageView(a_device->CastVulkan()->GetDevice(), m_swapChainImageViews[i], nullptr);

	vkDestroySwapchainKHR(a_device->CastVulkan()->GetDevice(), m_swapChain, nullptr);

	DEBUG_LOG_INFO("Vulkan SwapChain : SwapChain destroyed!\n");
}


SwapChainDetails VulkanSwapChain::GetSwapChainDetails(const VkPhysicalDevice a_device, const VkSurfaceKHR a_surface)
{
	SwapChainDetails l_swapChainDetails { };

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(a_device, a_surface, &l_swapChainDetails.surfaceCapabilities);

	uint32_t l_formatCount { 0 };
	vkGetPhysicalDeviceSurfaceFormatsKHR(a_device, a_surface, &l_formatCount, nullptr);

	if (l_formatCount != 0)
	{
		l_swapChainDetails.formats.resize(l_formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(a_device, a_surface, &l_formatCount, l_swapChainDetails.formats.data());
	}

	uint32_t l_presentationCount { 0 };
	vkGetPhysicalDeviceSurfacePresentModesKHR(a_device, a_surface, &l_presentationCount, nullptr);

	if (l_presentationCount != 0)
	{
		l_swapChainDetails.presentationModes.resize(l_presentationCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(a_device, a_surface, &l_presentationCount, l_swapChainDetails.presentationModes.data());
	}
	return l_swapChainDetails;
}


QueueFamilyIndices VulkanSwapChain::GetQueueFamilies(const VkPhysicalDevice a_device, const VkSurfaceKHR a_surface)
{
	QueueFamilyIndices l_indices { };

	uint32_t l_queueFamilyCount { 0 };
	vkGetPhysicalDeviceQueueFamilyProperties(a_device, &l_queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> l_queueFamilyList(l_queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(a_device, &l_queueFamilyCount, l_queueFamilyList.data());

	int l_i = 0;
	for (const VkQueueFamilyProperties& l_queueFamily : l_queueFamilyList)
	{
		if (l_queueFamily.queueCount > 0 && l_queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) l_indices.graphicsFamily = l_i;

		VkBool32 l_presentationSupport { false };
		vkGetPhysicalDeviceSurfaceSupportKHR(a_device, 1, a_surface, &l_presentationSupport);
		if (l_queueFamily.queueCount > 0 && l_presentationSupport) l_indices.presentationFamily = 1;

		if (l_indices.IsValid()) break;

		++l_i;
	}
	return l_indices;
}


VkSurfaceFormatKHR VulkanSwapChain::ChooseBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& a_formats)
{
	if (a_formats.size() == 1 && a_formats[0].format == VK_FORMAT_UNDEFINED) return { VK_FORMAT_R8G8B8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

	for (const auto& l_format : a_formats) { if ((l_format.format == VK_FORMAT_R8G8B8A8_UNORM || l_format.format == VK_FORMAT_B8G8R8A8_UNORM) && l_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) return l_format; }
	return a_formats[0];
}


VkPresentModeKHR VulkanSwapChain::ChooseBestPresentationMode(const std::vector<VkPresentModeKHR>& a_presentationModes)
{
	for (const auto& l_presentationMode : a_presentationModes)
		if (l_presentationMode == VK_PRESENT_MODE_MAILBOX_KHR) return l_presentationMode;

	return VK_PRESENT_MODE_FIFO_KHR;
}


VkExtent2D VulkanSwapChain::ChooseSwapExtend(const VkSurfaceCapabilitiesKHR& a_surfaceCapabilities, GLFWwindow* a_window)
{
	if (a_surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) return a_surfaceCapabilities.currentExtent;

	int l_width, l_height;
	glfwGetFramebufferSize(a_window, &l_width, &l_height);

	VkExtent2D l_newExtend = { };
	l_newExtend.width = static_cast<uint32_t>(l_width);
	l_newExtend.height = static_cast<uint32_t>(l_height);

	l_newExtend.width = std::min(a_surfaceCapabilities.minImageExtent.width, std::min(a_surfaceCapabilities.maxImageExtent.width, l_newExtend.width));
	l_newExtend.width = std::min(a_surfaceCapabilities.minImageExtent.height, std::min(a_surfaceCapabilities.maxImageExtent.height, l_newExtend.height));

	return l_newExtend;
}


VkImageView VulkanSwapChain::CreateImageView(const VkImage a_image, const VkDevice a_device, const VkFormat a_format, const VkImageAspectFlags a_aspectFlags)
{
	VkImageViewCreateInfo l_viewCreateInfo = { };

	l_viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	l_viewCreateInfo.image = a_image;
	l_viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	l_viewCreateInfo.format = a_format;
	l_viewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	l_viewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	l_viewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	l_viewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

	l_viewCreateInfo.subresourceRange.aspectMask = a_aspectFlags;
	l_viewCreateInfo.subresourceRange.baseMipLevel = 0;
	l_viewCreateInfo.subresourceRange.levelCount = 1;
	l_viewCreateInfo.subresourceRange.baseArrayLayer = 0;
	l_viewCreateInfo.subresourceRange.layerCount = 1;


	VkImageView l_imageView { };
	const VkResult l_result = vkCreateImageView(a_device, &l_viewCreateInfo, nullptr, &l_imageView);
	if (l_result != VK_SUCCESS)
		DEBUG_LOG_INFO("Failed to create an image View!!\n");

	return l_imageView;
}
