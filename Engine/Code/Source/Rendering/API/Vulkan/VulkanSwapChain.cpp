#include "Rendering/API/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/API/Vulkan/VulkanDevice.hpp"
#include "../Interface/IWindow.hpp"
#include "Rendering/API/Vulkan/VulkanWindow.hpp"

void VulkanSwapChain::Create(IWindow* a_window, IDevice* a_device,ISurface* a_surface)
{
	SwapChainDetails l_swapChainDetails = GetSwapChainDetails(a_device->CastVulkan()->GetPhysicalDevice(),a_surface->CastVulkan()->GetSurface());

	VkSurfaceFormatKHR l_surfaceFormat = ChooseBestSurfaceFormat(l_swapChainDetails.formats);
	VkPresentModeKHR l_presentMode = ChooseBestPresentationMode(l_swapChainDetails.presentationModes);
	VkExtent2D l_extent = ChooseSwapExtend(l_swapChainDetails.surfaceCapabilities, static_cast<VulkanWindow*>(a_window)->GetGLFWWindow());


	uint32_t l_imageCount = l_swapChainDetails.surfaceCapabilities.minImageCount + 1;
	if (l_swapChainDetails.surfaceCapabilities.maxImageCount > 0 && l_swapChainDetails.surfaceCapabilities.maxImageCount < l_imageCount) {
		l_imageCount = l_swapChainDetails.surfaceCapabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR l_swapChainCreateInfo = {};
	l_swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	l_swapChainCreateInfo.surface = a_surface->CastVulkan()->GetSurface();
	l_swapChainCreateInfo.minImageCount = l_imageCount;
	l_swapChainCreateInfo.imageFormat = l_surfaceFormat.format;
	l_swapChainCreateInfo.imageColorSpace = l_surfaceFormat.colorSpace;
	l_swapChainCreateInfo.imageExtent = l_extent;
	l_swapChainCreateInfo.imageArrayLayers = 1;
	l_swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	QueueFamilyIndices indices = GetQueueFamilies(a_device->CastVulkan()->GetPhysicalDevice(), a_surface->CastVulkan()->GetSurface());

	uint32_t queueFamilyIndices[] = {
		(uint32_t)indices.graphicsFamily,
		(uint32_t)indices.presentationFamily
	};

	if (indices.graphicsFamily != indices.presentationFamily) {
		l_swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		l_swapChainCreateInfo.queueFamilyIndexCount = 2;
		l_swapChainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else {
		l_swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		l_swapChainCreateInfo.queueFamilyIndexCount = 0;
		l_swapChainCreateInfo.pQueueFamilyIndices = nullptr;
	}

	l_swapChainCreateInfo.preTransform = l_swapChainDetails.surfaceCapabilities.currentTransform;
	l_swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	l_swapChainCreateInfo.presentMode = l_presentMode;
	l_swapChainCreateInfo.clipped = VK_TRUE;
	l_swapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

	VkResult result = vkCreateSwapchainKHR(a_device->CastVulkan()->GetDevice(), &l_swapChainCreateInfo, nullptr, &m_swapchain);
	if (result != VK_SUCCESS) {
		throw std::runtime_error("Failed to create a SwapChain");
	}

	vkGetSwapchainImagesKHR(a_device->CastVulkan()->GetDevice(), m_swapchain, &l_imageCount, nullptr);
	swapChainImages.resize(l_imageCount);
	vkGetSwapchainImagesKHR(a_device->CastVulkan()->GetDevice(), m_swapchain, &l_imageCount, swapChainImages.data());
	swapChainImageFormat = l_surfaceFormat.format;
	swapChainExtent = l_extent;

	swapChainImageViews.resize(swapChainImages.size());

	for (uint32_t i = 0; i < swapChainImages.size(); ++i) {
		swapChainImageViews[i] = CreateImageView(swapChainImages[i], a_device->CastVulkan()->GetDevice(), swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
	}
}

void VulkanSwapChain::Destroy(IDevice* a_device)
{
	std::cout << "DestroySwapChain\n";
}


SwapChainDetails VulkanSwapChain::GetSwapChainDetails(VkPhysicalDevice a_device , VkSurfaceKHR a_surface)
{
	SwapChainDetails l_swapChainDetails;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(a_device, a_surface, &l_swapChainDetails.surfaceCapabilities);

	uint32_t l_formatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(a_device, a_surface, &l_formatCount, nullptr);

	if (l_formatCount != 0) {
		l_swapChainDetails.formats.resize(l_formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(a_device, a_surface, &l_formatCount, l_swapChainDetails.formats.data());
	}

	uint32_t l_presentationCount = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(a_device, a_surface, &l_presentationCount, nullptr);

	if (l_presentationCount != 0) {
		l_swapChainDetails.presentationModes.resize(l_presentationCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(a_device, a_surface, &l_presentationCount, l_swapChainDetails.presentationModes.data());
	}
	return l_swapChainDetails;
}

QueueFamilyIndices VulkanSwapChain::GetQueueFamilies(VkPhysicalDevice a_device, VkSurfaceKHR a_surface)
{
	QueueFamilyIndices l_indices;

	uint32_t l_queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(a_device, &l_queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> l_queueFamilyList(l_queueFamilyCount);

	vkGetPhysicalDeviceQueueFamilyProperties(a_device, &l_queueFamilyCount, l_queueFamilyList.data());

	int l_i = 0;
	for (const VkQueueFamilyProperties& l_queueFamily : l_queueFamilyList) {

		if (l_queueFamily.queueCount > 0 && l_queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			l_indices.graphicsFamily = l_i;
		}

		VkBool32 l_presentationSupport = false;

		vkGetPhysicalDeviceSurfaceSupportKHR(a_device, 1, a_surface, &l_presentationSupport);
		if (l_queueFamily.queueCount > 0 && l_presentationSupport) {
			l_indices.presentationFamily = 1;
		}

		if (l_indices.IsValid()) {
			break;
		}
		++l_i;
	}
	return l_indices;
}


VkSurfaceFormatKHR VulkanSwapChain::ChooseBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& a_formats)
{
	if (a_formats.size() == 1 && a_formats[0].format == VK_FORMAT_UNDEFINED) {
		return { VK_FORMAT_R8G8B8A8_UNORM,VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
	}

	for (const auto& l_format : a_formats) {
		if ((l_format.format == VK_FORMAT_R8G8B8A8_UNORM || l_format.format == VK_FORMAT_B8G8R8A8_UNORM) && l_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return l_format;
		}
	}
	return a_formats[0];
}

VkPresentModeKHR VulkanSwapChain::ChooseBestPresentationMode(const std::vector<VkPresentModeKHR> a_presentationModes)
{
	for (const auto& l_presentationMode : a_presentationModes) {
		if (l_presentationMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return l_presentationMode;
		}
	}
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanSwapChain::ChooseSwapExtend(const VkSurfaceCapabilitiesKHR& a_surfaceCapabilities, GLFWwindow* a_window)
{
	if (a_surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return a_surfaceCapabilities.currentExtent;
	}
	else {
		int l_width, l_height;
		glfwGetFramebufferSize(a_window, &l_width, &l_height);

		VkExtent2D l_newExtend = {};
		l_newExtend.width = static_cast<uint32_t>(l_width);
		l_newExtend.height = static_cast<uint32_t>(l_height);

		l_newExtend.width = std::min(a_surfaceCapabilities.minImageExtent.width, std::min(a_surfaceCapabilities.maxImageExtent.width, l_newExtend.width));
		l_newExtend.width = std::min(a_surfaceCapabilities.minImageExtent.height, std::min(a_surfaceCapabilities.maxImageExtent.height, l_newExtend.height));

		return l_newExtend;
	}
}

VkImageView VulkanSwapChain::CreateImageView(VkImage a_image, VkDevice a_device, VkFormat a_format, VkImageAspectFlags a_aspectFlags)
{
	VkImageViewCreateInfo l_viewCreateInfo = {};

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


	VkImageView l_imageView;

	VkResult result = vkCreateImageView(a_device, &l_viewCreateInfo, nullptr, &l_imageView);

	if (result != VK_SUCCESS) {
		throw std::runtime_error("Failed to create an image View!");
	}
	return l_imageView;
}