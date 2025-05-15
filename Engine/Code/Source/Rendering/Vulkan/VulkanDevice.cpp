#include <iostream>
#include <set>
#include <vector>

#include "IInstance.hpp"
#include "ISurface.hpp"

#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanInstance.hpp"
#include "Rendering/Vulkan/VulkanSurface.hpp"
#include "Rendering/Vulkan/VulkanValidationLayer.hpp"


void VulkanDevice::Create(IInstance* a_instance, ISurface* a_surface)
{
	const VkSurfaceKHR& l_vkSurface = a_surface->CastVulkan()->GetSurface();

	GetPhysicalDevice(a_instance->CastVulkan()->GetInstance(), l_vkSurface);
	CreateLogicalDevice(l_vkSurface);
	DEBUG_LOG_INFO("Vulkan Device : Device Created!\n");
}


void VulkanDevice::Destroy()
{
	vkDestroyDevice(m_device, nullptr);
	DEBUG_LOG_INFO("Vulkan Device : Device destroyed!\n");
}


void VulkanDevice::CreateLogicalDevice(const VkSurfaceKHR& a_surface)
{
	const QueueFamilyIndices l_indices = GetQueueFamilies(m_physicalDevice, a_surface);
	ProcessLogicalDeviceInfo(l_indices);
	vkGetDeviceQueue(m_device, l_indices.graphicsFamily, 0, &m_graphicsQueue);
	vkGetDeviceQueue(m_device, l_indices.presentationFamily, 0, &m_presentationQueue);
}


void VulkanDevice::GetPhysicalDevice(const VkInstance& a_instance, const VkSurfaceKHR& a_surface)
{
	uint32_t l_deviceCount = 0;
	vkEnumeratePhysicalDevices(a_instance, &l_deviceCount, nullptr);
	if (l_deviceCount == 0)
		DEBUG_LOG_ERROR("can't find GPUs that support Vulkan Instance!\n");

	std::vector<VkPhysicalDevice> l_deviceList { l_deviceCount };
	vkEnumeratePhysicalDevices(a_instance, &l_deviceCount, l_deviceList.data());
	for (const VkPhysicalDevice& l_device : l_deviceList)
	{
		if (CheckDeviceSuitable(l_device, a_surface))
		{
			m_physicalDevice = l_device;
			break;
		}
	}
}


bool VulkanDevice::CheckDeviceSuitable(const VkPhysicalDevice& a_device, const VkSurfaceKHR& a_surface)
{
	VkPhysicalDeviceProperties l_deviceProperties { };
	vkGetPhysicalDeviceProperties(a_device, &l_deviceProperties);

	VkPhysicalDeviceFeatures l_deviceFeatures { };
	vkGetPhysicalDeviceFeatures(a_device, &l_deviceFeatures);
    

	QueueFamilyIndices l_indices = GetQueueFamilies(a_device, a_surface);
	bool l_extensionSupported = CheckDeviceExtensionSupport(a_device);
	bool l_swapChainValid = false;

	if (l_extensionSupported)
	{
		SwapChainDetails swapChainDetails = GetSwapChainDetails(a_device, a_surface);
		l_swapChainValid = !swapChainDetails.presentationModes.empty() && !swapChainDetails.formats.empty();
	}
	return l_indices.IsValid() && l_extensionSupported && l_swapChainValid;
}


SwapChainDetails VulkanDevice::GetSwapChainDetails(const VkPhysicalDevice& a_device, const VkSurfaceKHR& a_surface)
{
	SwapChainDetails l_swapChainDetails { };
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(a_device, a_surface, &l_swapChainDetails.surfaceCapabilities);

	uint32_t l_formatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(a_device, a_surface, &l_formatCount, nullptr);

	if (l_formatCount != 0)
	{
		l_swapChainDetails.formats.resize(l_formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(a_device, a_surface, &l_formatCount, l_swapChainDetails.formats.data());
	}

	uint32_t l_presentationCount = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(a_device, a_surface, &l_presentationCount, nullptr);

	if (l_presentationCount != 0)
	{
		l_swapChainDetails.presentationModes.resize(l_presentationCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(a_device, a_surface, &l_presentationCount, l_swapChainDetails.presentationModes.data());
	}
	return l_swapChainDetails;
}


bool VulkanDevice::CheckDeviceExtensionSupport(const VkPhysicalDevice& a_device)
{
	uint32_t l_extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(a_device, nullptr, &l_extensionCount, nullptr);

	if (l_extensionCount == 0)
		return false;

	std::vector<VkExtensionProperties> l_extensions(l_extensionCount);
	vkEnumerateDeviceExtensionProperties(a_device, nullptr, &l_extensionCount, l_extensions.data());

	for (const auto& l_deviceExtension : deviceExtensions)
	{
		bool l_hasExtension = false;
		for (const auto& l_extension : l_extensions)
		{
			if (strcmp(l_deviceExtension, l_extension.extensionName) == 0)
			{
				l_hasExtension = true;
				break;
			}
		}

		if (!l_hasExtension) return false;
	}
	return true;
}


QueueFamilyIndices VulkanDevice::GetQueueFamilies(const VkPhysicalDevice& a_device, const VkSurfaceKHR& a_surface)
{
	uint32_t l_queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(a_device, &l_queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> l_queueFamilyList { l_queueFamilyCount };
	vkGetPhysicalDeviceQueueFamilyProperties(a_device, &l_queueFamilyCount, l_queueFamilyList.data());

	QueueFamilyIndices l_indices { };
	for (unsigned int i = 0; i < l_queueFamilyList.size(); ++i)
	{
		if (l_queueFamilyList[i].queueCount > 0 && l_queueFamilyList[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			l_indices.graphicsFamily = i;

		VkBool32 l_presentationSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(a_device, 1, a_surface, &l_presentationSupport);
		if (l_queueFamilyList[i].queueCount > 0 && l_presentationSupport) l_indices.presentationFamily = 1;

		if (l_indices.IsValid())
			break;
	}
	return l_indices;
}


void VulkanDevice::WaitIdle() const
{
    const VkResult l_idleResult = { vkDeviceWaitIdle(m_device) };
    if (l_idleResult == VK_SUCCESS)
        return;

    DEBUG_LOG_ERROR("Device still has commands waiting for execution!");
}

void VulkanDevice::ProcessLogicalDeviceInfo(const QueueFamilyIndices& a_queueFamilyIndices)
{
	const std::set<int> l_queueFamilyIndices = { a_queueFamilyIndices.graphicsFamily, a_queueFamilyIndices.presentationFamily };
	std::vector<VkDeviceQueueCreateInfo> l_queueCreateInfos { };
	AssignQueueFamilyIndices(l_queueFamilyIndices, l_queueCreateInfos);

	VkPhysicalDeviceFeatures l_physicalDeviceFeatures { };
	l_physicalDeviceFeatures.samplerAnisotropy = VK_TRUE;
    l_physicalDeviceFeatures.sampleRateShading = VK_TRUE;
    l_physicalDeviceFeatures.fillModeNonSolid = VK_TRUE;

	VkDeviceCreateInfo l_deviceCreateInfo { };
    l_deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	l_deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(l_queueCreateInfos.size());
	l_deviceCreateInfo.pQueueCreateInfos = l_queueCreateInfos.data();
	l_deviceCreateInfo.pEnabledFeatures = &l_physicalDeviceFeatures;
	l_deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	l_deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
    l_deviceCreateInfo.pNext = nullptr;


	if (ValidationLayer::ValidationLayersEnabled)
	{
		l_deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayer::ValidationLayers.size());
		l_deviceCreateInfo.ppEnabledLayerNames = ValidationLayer::ValidationLayers.data();
	}

	const VkResult l_result = vkCreateDevice(m_physicalDevice, &l_deviceCreateInfo, nullptr, &m_device);
	if (l_result != VK_SUCCESS)
		throw std::runtime_error("Failed to create a logical device!");
}


void VulkanDevice::AssignQueueFamilyIndices(const std::set<int>& a_queueFamilyIndices, std::vector<VkDeviceQueueCreateInfo>& a_queueCreateInfos)
{
	const float l_priority { 1.0f };
	for (const int l_queueFamilyIndex : a_queueFamilyIndices)
	{
		VkDeviceQueueCreateInfo l_queueCreateInfo { };
	    l_queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		l_queueCreateInfo.queueFamilyIndex = l_queueFamilyIndex;
		l_queueCreateInfo.queueCount = 1;
		l_queueCreateInfo.pQueuePriorities = &l_priority;
	    l_queueCreateInfo.pNext = nullptr;

		a_queueCreateInfos.push_back(l_queueCreateInfo); // vulkan needs to know how to handle multiple queues, so choose properly ( 1 = highest priority)
	}
}