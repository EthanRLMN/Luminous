#include "Rendering/API/Vulkan/VulkanDevice.hpp"

#include <set>
#include <vector>

#include "IInstance.hpp"
#include "ISurface.hpp"
#include "Rendering/API/Vulkan/VulkanInstance.hpp"
#include "Rendering/API/Vulkan/VulkanSurface.hpp"

#include "Rendering/API/Vulkan/VulkanValidationLayer.hpp"

void VulkanDevice::Create(IInstance* a_instance, IWindow* a_window, ISurface* a_surface)
{
	const VkInstance l_vkPhysDevice = a_instance->CastVulkan()->GetInstance();
	const VkSurfaceKHR l_vkSurface = a_surface->CastVulkan()->GetSurface();

	GetPhysicalDevice(l_vkPhysDevice, l_vkSurface);
	CreateLogicalDevice(l_vkSurface, l_vkPhysDevice);
}

void VulkanDevice::Destroy()
{
	DEBUG_LOG_INFO("Vulkan Device : Device destroyed!\n");
}

void VulkanDevice::CreateLogicalDevice(const VkSurfaceKHR a_surface, VkInstance a_instance)
{
	QueueFamilyIndices l_indices = GetQueueFamilies(m_physicalDevice, a_surface);

	std::vector<VkDeviceQueueCreateInfo> l_queueCreateInfos;
	std::set<int> l_queueFamilyIndices = {l_indices.graphicsFamily, l_indices.presentationFamily};


	float l_priority = 1.0f;

	for (int l_queueFamilyIndex: l_queueFamilyIndices)
	{
		VkDeviceQueueCreateInfo l_queueCreateInfo = {};
		l_queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		l_queueCreateInfo.queueFamilyIndex = l_queueFamilyIndex;
		l_queueCreateInfo.queueCount = 1;
		l_queueCreateInfo.pQueuePriorities = &l_priority;
		// vulkan need to know how to handle multiple queues, so decide property ( 1 = highest prioryty)
		l_queueCreateInfos.push_back(l_queueCreateInfo);
	}

	VkPhysicalDeviceFeatures l_physicalDeviceFeatures = {};
	l_physicalDeviceFeatures.samplerAnisotropy = VK_TRUE;


	VkDeviceCreateInfo l_deviceCreateInfo = {};
	l_deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	l_deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(l_queueCreateInfos.size());
	l_deviceCreateInfo.pQueueCreateInfos = l_queueCreateInfos.data();
	l_deviceCreateInfo.pEnabledFeatures = &l_physicalDeviceFeatures;
	l_deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	l_deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

	if (validationEnabled)
	{
		l_deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		l_deviceCreateInfo.ppEnabledLayerNames = validationLayers.data();
	}

	if (VkResult l_result = vkCreateDevice(m_physicalDevice, &l_deviceCreateInfo, nullptr, &m_device); l_result != VK_SUCCESS)
		throw std::runtime_error("failed to create a logical device");

	vkGetDeviceQueue(m_device, l_indices.graphicsFamily, 0, &m_graphicsQueue);
	vkGetDeviceQueue(m_device, l_indices.presentationFamily, 0, &m_presentationQueue);
}

void VulkanDevice::GetPhysicalDevice(const VkInstance a_instance, const VkSurfaceKHR a_surface)
{
	uint32_t l_deviceCount = 0;
	vkEnumeratePhysicalDevices(a_instance, &l_deviceCount, nullptr);


	if (l_deviceCount == 0)
		throw std::runtime_error("can't find GPUs that support Vulkan Instance");

	std::vector<VkPhysicalDevice> l_deviceList(l_deviceCount);
	vkEnumeratePhysicalDevices(a_instance, &l_deviceCount, l_deviceList.data());

	for (const VkPhysicalDevice& l_device: l_deviceList)
	{
		if (CheckDeviceSuitable(l_device, a_surface))
		{
			m_physicalDevice = l_device;
			break;
		}
	}
}


bool VulkanDevice::CheckDeviceSuitable(VkPhysicalDevice a_device, VkSurfaceKHR a_surface)
{
	VkPhysicalDeviceProperties l_deviceProperties{};
	vkGetPhysicalDeviceProperties(a_device, &l_deviceProperties);

	VkPhysicalDeviceFeatures l_deviceFeatures{};
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

SwapChainDetails VulkanDevice::GetSwapChainDetails(const VkPhysicalDevice a_device, const VkSurfaceKHR a_surface)
{
	SwapChainDetails l_swapChainDetails{};

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
		vkGetPhysicalDeviceSurfacePresentModesKHR(a_device, a_surface, &l_presentationCount,
		                                          l_swapChainDetails.presentationModes.data());
	}
	return l_swapChainDetails;
}

bool VulkanDevice::CheckDeviceExtensionSupport(VkPhysicalDevice a_device)
{
	uint32_t l_extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(a_device, nullptr, &l_extensionCount, nullptr);

	if (l_extensionCount == 0)
		return false;

	std::vector<VkExtensionProperties> l_extensions(l_extensionCount);
	vkEnumerateDeviceExtensionProperties(a_device, nullptr, &l_extensionCount, l_extensions.data());

	for (const auto& l_deviceExtension: deviceExtensions)
	{
		bool l_hasExtension = false;
		for (const auto& l_extension: l_extensions)
		{
			if (strcmp(l_deviceExtension, l_extension.extensionName) == 0)
			{
				l_hasExtension = true;
				break;
			}
		}

		if (!l_hasExtension)
			return false;

	}
	return true;
}


QueueFamilyIndices VulkanDevice::GetQueueFamilies(const VkPhysicalDevice a_device, const VkSurfaceKHR a_surface)
{
	QueueFamilyIndices l_indices{};

	uint32_t l_queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(a_device, &l_queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> l_queueFamilyList(l_queueFamilyCount);

	vkGetPhysicalDeviceQueueFamilyProperties(a_device, &l_queueFamilyCount, l_queueFamilyList.data());

	int l_i = 0;
	for (const VkQueueFamilyProperties& l_queueFamily: l_queueFamilyList)
	{
		if (l_queueFamily.queueCount > 0 && l_queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			l_indices.graphicsFamily = l_i;

		VkBool32 l_presentationSupport = false;

		vkGetPhysicalDeviceSurfaceSupportKHR(a_device, 1, a_surface, &l_presentationSupport);
		if (l_queueFamily.queueCount > 0 && l_presentationSupport)
			l_indices.presentationFamily = 1;

		if (l_indices.IsValid())
			break;

		++l_i;
	}
	return l_indices;
}
