#include "IWindow.hpp"

#include "Core/GLFW/GLFWWindow.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"


void VulkanSwapChain::Create(IWindow* a_window, IDevice* a_device, ISurface* a_surface)
{
    const VkPhysicalDevice l_vkPhysDevice = a_device->CastVulkan()->GetPhysicalDevice();
    const VkDevice l_vkDevice = a_device->CastVulkan()->GetDevice();
    const VkSurfaceKHR l_vkSurface = a_surface->CastVulkan()->GetSurface();
    const SwapChainDetails l_swapChainDetails = GetSwapChainDetails(l_vkPhysDevice, l_vkSurface);
    const VkSurfaceFormatKHR l_surfaceFormat = ChooseBestSurfaceFormat(l_swapChainDetails.formats);
    const VkPresentModeKHR l_presentMode = ChooseBestPresentationMode(l_swapChainDetails.presentationModes);
    const VkExtent2D l_extent = ChooseSwapExtent(l_swapChainDetails.surfaceCapabilities, dynamic_cast<GLFWWindow*>(a_window)->GetGLFWWindow());

    uint32_t l_imageCount = l_swapChainDetails.surfaceCapabilities.minImageCount + 1;
    if (l_swapChainDetails.surfaceCapabilities.maxImageCount > 0 && l_swapChainDetails.surfaceCapabilities.maxImageCount < l_imageCount)
        l_imageCount = l_swapChainDetails.surfaceCapabilities.maxImageCount;

    VkSwapchainCreateInfoKHR l_swapChainCreateInfo = { VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
    FillSwapChainCreationInfo(l_swapChainCreateInfo, a_surface->CastVulkan()->GetSurface(), l_imageCount, l_surfaceFormat, l_extent);

    const QueueFamilyIndices l_indices = GetQueueFamilies(l_vkPhysDevice, l_vkSurface);
    const std::vector<uint32_t> l_queueFamilyIndices = { static_cast<uint32_t>(l_indices.graphicsFamily), static_cast<uint32_t>(l_indices.presentationFamily) };
    FillSwapChainGraphicsFamilyData(l_swapChainCreateInfo, l_indices, l_queueFamilyIndices, l_swapChainDetails, l_presentMode);

    const VkResult l_result = vkCreateSwapchainKHR(l_vkDevice, &l_swapChainCreateInfo, nullptr, &m_swapChain);
    if (l_result != VK_SUCCESS)
        DEBUG_LOG_ERROR("Failed to create a SwapChain\n");

    SendSwapChainData(l_vkDevice, l_imageCount, l_surfaceFormat, l_extent);
    DEBUG_LOG_INFO("Vulkan SwapChain : SwapChain created!\n");
}


void VulkanSwapChain::Destroy(IDevice* a_device)
{
    for (size_t i{ 0 }; i < m_swapChainImageViews.size(); ++i)
        vkDestroyImageView(a_device->CastVulkan()->GetDevice(), m_swapChainImageViews[i], nullptr);

    vkDestroySwapchainKHR(a_device->CastVulkan()->GetDevice(), m_swapChain, nullptr);
    DEBUG_LOG_INFO("Vulkan SwapChain : SwapChain destroyed!\n");
}


SwapChainDetails VulkanSwapChain::GetSwapChainDetails(const VkPhysicalDevice a_device, const VkSurfaceKHR a_surface)
{
    SwapChainDetails l_swapChainDetails{};
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(a_device, a_surface, &l_swapChainDetails.surfaceCapabilities);

    uint32_t l_formatCount{ 0 };
    vkGetPhysicalDeviceSurfaceFormatsKHR(a_device, a_surface, &l_formatCount, nullptr);

    if (l_formatCount != 0)
    {
        l_swapChainDetails.formats.resize(l_formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(a_device, a_surface, &l_formatCount, l_swapChainDetails.formats.data());
    }

    uint32_t l_presentationCount{ 0 };
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
    QueueFamilyIndices l_indices{};
    uint32_t l_queueFamilyCount{ 0 };
    vkGetPhysicalDeviceQueueFamilyProperties(a_device, &l_queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> l_queueFamilyList(l_queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(a_device, &l_queueFamilyCount, l_queueFamilyList.data());
    for (unsigned int i = 0; i < l_queueFamilyList.size(); ++i)
    {
        if (l_queueFamilyList[i].queueCount > 0 && l_queueFamilyList[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            l_indices.graphicsFamily = static_cast<int>(i);

        VkBool32 l_presentationSupport{ false };
        vkGetPhysicalDeviceSurfaceSupportKHR(a_device, 1, a_surface, &l_presentationSupport);
        if (l_queueFamilyList[i].queueCount > 0 && l_presentationSupport)
            l_indices.presentationFamily = 1;

        if (l_indices.IsValid())
            break;
    }
    return l_indices;
}


VkSurfaceFormatKHR VulkanSwapChain::ChooseBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& a_formats)
{
    if (a_formats.size() == 1 && a_formats[0].format == VK_FORMAT_UNDEFINED)
        return { VK_FORMAT_R8G8B8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

    for (const VkSurfaceFormatKHR& l_format : a_formats)
        if ((l_format.format == VK_FORMAT_R8G8B8A8_UNORM || l_format.format == VK_FORMAT_B8G8R8A8_UNORM) && l_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            return l_format;

    return a_formats[0];
}


VkPresentModeKHR VulkanSwapChain::ChooseBestPresentationMode(const std::vector<VkPresentModeKHR>& a_presentationModes)
{
    for (const auto& l_presentationMode : a_presentationModes)
        if (l_presentationMode == VK_PRESENT_MODE_MAILBOX_KHR)
            return l_presentationMode;

    return VK_PRESENT_MODE_FIFO_KHR;
}


VkExtent2D VulkanSwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& a_surfaceCapabilities, GLFWwindow* a_window)
{
    if (a_surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
        return a_surfaceCapabilities.currentExtent;

    int l_width{ 1280 };
    int l_height{ 720 };
    glfwGetFramebufferSize(a_window, &l_width, &l_height);

    VkExtent2D l_newExtent = {
        .width = std::min(a_surfaceCapabilities.minImageExtent.width, std::min(a_surfaceCapabilities.maxImageExtent.width, l_newExtent.width)),
        .height = std::min(a_surfaceCapabilities.minImageExtent.height, std::min(a_surfaceCapabilities.maxImageExtent.height, l_newExtent.height))
    };

    return l_newExtent;
}

void VulkanSwapChain::FillSwapChainCreationInfo(VkSwapchainCreateInfoKHR& a_swapChainCreateInfo, const VkSurfaceKHR& a_surface, const uint32_t a_imageCount, const VkSurfaceFormatKHR& a_surfaceFormat, const VkExtent2D& a_extent)
{
    a_swapChainCreateInfo.surface = a_surface;
    a_swapChainCreateInfo.minImageCount = a_imageCount;
    a_swapChainCreateInfo.imageFormat = a_surfaceFormat.format;
    a_swapChainCreateInfo.imageColorSpace = a_surfaceFormat.colorSpace;
    a_swapChainCreateInfo.imageExtent = a_extent;
    a_swapChainCreateInfo.imageArrayLayers = 1;
    a_swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
}


void VulkanSwapChain::FillSwapChainGraphicsFamilyData(VkSwapchainCreateInfoKHR& a_swapChainCreateInfo, const QueueFamilyIndices& a_indices, const std::vector<uint32_t>& a_queueFamilyIndices, const SwapChainDetails& a_swapChainDetails, const VkPresentModeKHR& a_presentMode)
{
    if (a_indices.graphicsFamily != a_indices.presentationFamily)
    {
        a_swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        a_swapChainCreateInfo.queueFamilyIndexCount = 2;
        a_swapChainCreateInfo.pQueueFamilyIndices = a_queueFamilyIndices.data();
    } else
    {
        a_swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        a_swapChainCreateInfo.queueFamilyIndexCount = 0;
        a_swapChainCreateInfo.pQueueFamilyIndices = nullptr;
    }

    a_swapChainCreateInfo.preTransform = a_swapChainDetails.surfaceCapabilities.currentTransform;
    a_swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    a_swapChainCreateInfo.presentMode = a_presentMode;
    a_swapChainCreateInfo.clipped = VK_TRUE;
    a_swapChainCreateInfo.oldSwapchain = nullptr;
}


void VulkanSwapChain::SendSwapChainData(const VkDevice& a_vkDevice, uint32_t& a_imageCount, const VkSurfaceFormatKHR& a_surfaceFormat, const VkExtent2D& a_extent)
{
    vkGetSwapchainImagesKHR(a_vkDevice, m_swapChain, &a_imageCount, nullptr);
    m_swapChainImages.resize(a_imageCount);

    vkGetSwapchainImagesKHR(a_vkDevice, m_swapChain, &a_imageCount, m_swapChainImages.data());
    m_swapChainImageFormat = a_surfaceFormat.format;
    m_swapChainExtent = a_extent;
    m_swapChainImageViews.resize(m_swapChainImages.size());

    for (uint32_t i{ 0 }; i < m_swapChainImages.size(); ++i)
        m_swapChainImageViews[i] = CreateImageView(m_swapChainImages[i], a_vkDevice, m_swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
}


VkImageView VulkanSwapChain::CreateImageView(const VkImage a_image, const VkDevice a_device, const VkFormat a_format, const VkImageAspectFlags a_aspectFlags)
{
    VkImageViewCreateInfo l_viewCreateInfo = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
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

    VkImageView l_imageView{};
    const VkResult l_result = vkCreateImageView(a_device, &l_viewCreateInfo, nullptr, &l_imageView);
    if (l_result != VK_SUCCESS)
        DEBUG_LOG_INFO("Failed to create an image View!!\n");

    return l_imageView;
}
