#include "Rendering/API/Vulkan/VulkanDevice.hpp"

#include <cstring>
#include <set>
#include <vector>

#include "IInstance.hpp"
#include "ISurface.hpp"
#include "Rendering/API/Vulkan/VulkanInstance.hpp"
#include "Rendering/API/Vulkan/VulkanSurface.hpp"

void VulkanDevice::Create(IInstance* a_instance, IWindow* a_window, ISurface* a_surface)
{
	std::cout << "Create Device\n";

	GetPhysicalDevice(a_instance->CastVulkan()->GetInstance(), a_surface->CastVulkan()->GetSurface());
	CreateLogicalDevice(a_surface->CastVulkan()->GetSurface(), a_instance->CastVulkan()->GetInstance());

	std::cout << "FinishDevice\n";
}

void VulkanDevice::Destroy()
{
	std::cout << "Destroy Device\n";
}

void VulkanDevice::CreateLogicalDevice(const VkSurfaceKHR a_surface, VkInstance a_instance)
{
	//get the queue family indices for chosen physical device
	QueueFamilyIndices l_indices = GetQueueFamilies(m_physicalDevice, a_surface);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<int> l_queueFamilyIndices = {l_indices.graphicsFamily, l_indices.presentationFamily};

	//Queues the logical device and to create and info to do so (only 1 the rest i will do later)

	for (int queueFamilyIndex: l_queueFamilyIndices)
	{
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamilyIndex; //index of family to create a queue from
		queueCreateInfo.queueCount = 1; // number of queues to create

		float priority = 1.0f;
		queueCreateInfo.pQueuePriorities = &priority;
		// vulkan need to know how to handle multiple queues, so decide property ( 1 = highest priority)

		queueCreateInfos.push_back(queueCreateInfo);
	}

	//information to create logicaldevice (sometimes called "device")
	VkDeviceCreateInfo deviceCreateInfo = {};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	// number of queue create info
	deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
	// list of queue create infos so device can create required queues
	deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	// number of enabled logical device extensions
	deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();; // list of enable logical device
	deviceCreateInfo.enabledLayerCount = 0; /// deprecate necessaire seulement a VK 1.0

	//physical device features the logical device will use
	VkPhysicalDeviceFeatures deviceFeatures = {};
	deviceCreateInfo.pEnabledFeatures = &deviceFeatures; // physical device features logical device will use


	//create logical device for given physical device

	if (VkResult l_result = vkCreateDevice(m_physicalDevice, &deviceCreateInfo, nullptr, &m_device); l_result != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create a logical device");
	}

	//queue are created at the same time as the device so we handle to queues from given logical device ,of given queue family ,of given index (0since only one queue), place reference in given vkqueue
	vkGetDeviceQueue(m_device, l_indices.graphicsFamily, 0, &m_graphicsQueue);
	vkGetDeviceQueue(m_device, l_indices.presentationFamily, 0, &m_presentationQueue);
}

void VulkanDevice::GetPhysicalDevice(const VkInstance a_instance, const VkSurfaceKHR a_surface)
{
	//Enumerate Physical devices the vkInstance can access
	uint32_t l_deviceCount = 0;
	vkEnumeratePhysicalDevices(a_instance, &l_deviceCount, nullptr);

	//check if device is available
	if (l_deviceCount == 0)
		throw std::runtime_error("can't find GPUs that support Vulkan Instance");

	//get list of physical device
	std::vector<VkPhysicalDevice> l_deviceList(l_deviceCount);
	vkEnumeratePhysicalDevices(a_instance, &l_deviceCount, l_deviceList.data());

	for (const auto& l_device: l_deviceList)
	{
		if (CheckDeviceSuitable(l_device, a_surface))
		{
			m_physicalDevice = l_device;
			break;
		}
	}
}


bool VulkanDevice::CheckDeviceSuitable(const VkPhysicalDevice a_device, const VkSurfaceKHR a_surface)
{
	//Information about the device itself
	VkPhysicalDeviceProperties l_deviceProperties;
	vkGetPhysicalDeviceProperties(a_device, &l_deviceProperties);

	//information about what device can do (geo shader , tess shader , wide lines ,etc)
	VkPhysicalDeviceFeatures l_deviceFeatures;
	vkGetPhysicalDeviceFeatures(a_device, &l_deviceFeatures);

	const QueueFamilyIndices l_indices = GetQueueFamilies(a_device, a_surface);

	const bool l_extensionSupported = CheckDeviceExtensionSupport(a_device);

	bool l_swapChainValid = false;

	if (l_extensionSupported)
	{
		const SwapChainDetails l_swapChainDetails = GetSwapChainDetails(a_device, a_surface);
		l_swapChainValid = !l_swapChainDetails.presentationModes.empty() && !l_swapChainDetails.formats.empty();
	}

	return l_indices.IsValid() && l_extensionSupported && l_swapChainValid;
}

bool VulkanDevice::CheckDeviceExtensionSupport(const VkPhysicalDevice a_device)
{
	// Get device extension count
	uint32_t l_extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(a_device, nullptr, &l_extensionCount, nullptr);

	// If no extensions found, return failure
	if (l_extensionCount == 0)
	{
		return false;
	}

	// Populate list of extensions
	std::vector<VkExtensionProperties> l_extensions(l_extensionCount);
	vkEnumerateDeviceExtensionProperties(a_device, nullptr, &l_extensionCount, l_extensions.data());

	// Check for extension
	for (const auto& deviceExtension: deviceExtensions)
	{
		bool l_hasExtension = false;
		for (const auto& l_extension: l_extensions)
		{
			if (strcmp(deviceExtension, l_extension.extensionName) == 0)
			{
				l_hasExtension = true;
				break;
			}
		}

		if (!l_hasExtension)
		{
			return false;
		}
	}

	return true;
}


QueueFamilyIndices VulkanDevice::GetQueueFamilies(const VkPhysicalDevice a_device, const VkSurfaceKHR a_surface)
{
	QueueFamilyIndices l_indices;

	uint32_t l_queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(a_device, &l_queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> l_queueFamilyList(l_queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(a_device, &l_queueFamilyCount, l_queueFamilyList.data());

	//go through each queue family and check if it has at least 1 of the required types of queue
	int i = 0;
	for (const auto& l_queueFamily: l_queueFamilyList)
	{
		//first check if queue family has at least 1 queue in that family (could have no queues) + queue can be multiple types defined through bitfield
		if (l_queueFamily.queueCount > 0 && l_queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			l_indices.graphicsFamily = i; // if queue family is valid, get index

		//checkqueuefamily support presentation
		VkBool32 l_presentationSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(a_device, i, a_surface, &l_presentationSupport);
		//check if queue is representation type (cna be graphic an presentation )
		if (l_queueFamily.queueCount > 0 && l_presentationSupport)
			l_indices.presentationFamily = 1;

		if (l_indices.IsValid())
			break;

		++i;
	}
	return l_indices;
}


SwapChainDetails VulkanDevice::GetSwapChainDetails(const VkPhysicalDevice a_device, const VkSurfaceKHR a_surface)
{
	SwapChainDetails l_swapChainDetails;

	//Get surface capabilities for the given surface o nthe given physical device
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(a_device, a_surface, &l_swapChainDetails.surfaceCapabilities);


	uint32_t l_formatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(a_device, a_surface, &l_formatCount, nullptr);

	if (l_formatCount != 0)
	{
		l_swapChainDetails.formats.resize(l_formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(a_device, a_surface, &l_formatCount, l_swapChainDetails.formats.data());
	}

	//presentation modes

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

VkPhysicalDevice VulkanDevice::GetPhysicalDevice() const
{
	return m_physicalDevice;
}

VkQueue VulkanDevice::GetGraphicsQueue() const
{
	return m_graphicsQueue;
}


