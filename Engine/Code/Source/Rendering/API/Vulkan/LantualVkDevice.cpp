#include "LantualVkDevice.h"
#include "LantualVkSwapChain.h"

void LantualVkDevice::Create(LantualInstance* _instance, Window* _window, LantualSurface* _surface)
{
	std::cout << "Create Device" << std::endl; 

	GetPhysicalDevice(_instance->GetInstance(), _surface->CastVulkan()->GetSurface());
	CreateLogicalDevice(_surface->GetSurface(), _instance->GetInstance());
	
	std::cout << "FinishDevice" << std::endl;
}

void LantualVkDevice::Destroy()
{
	std::cout << "Destroy Device" << std::endl;
}

void LantualVkDevice::CreateLogicalDevice(VkSurfaceKHR _surface, VkInstance _instance)
{
	//get the queue family  indices for chosen physical device
	QueueFamilyIndices indices = getQueueFamilies(physicalDevice,_surface);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<int> queueFamilyIndices = { indices.graphicsFamily , indices.presentationFamily };

	//Queues the logical device eeet to create and info to do so (only 1 the rest i will do later)

	for (int queueFamilyIndex : queueFamilyIndices) {
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamilyIndex; //index of family to creata a queue from
		queueCreateInfo.queueCount = 1; // number of queues to create

		float priority = 1.0f;
		queueCreateInfo.pQueuePriorities = &priority; // vulkan need to know how to handle multiple queues, so decide property ( 1 = highest prioryty)

		queueCreateInfos.push_back(queueCreateInfo);
	}

	//information to create logicaldevice (sometimes called "device")
	VkDeviceCreateInfo deviceCreateInfo = {};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()); // number of queue create info
	deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data(); // list of queue crete infos so device can create required queues
	deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()); // number of enabled logical device extensions
	deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();; // list of enable logical device
	deviceCreateInfo.enabledLayerCount = 0; /// deprecate necessaire seulement a VK 1.0

	//physical device features the logical device will using
	VkPhysicalDeviceFeatures deviceFeatures = {};
	deviceCreateInfo.pEnabledFeatures = &deviceFeatures; // physical device features logical device will use


	//create logical device for given physical device
	VkResult result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);

	if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to create a logical device");

	}

	//queue are created at the same time as the device so we ahndle to queues from given logical device ,of given queue family ,of given index (0since only one queue), place reference in given vkqueue
	vkGetDeviceQueue(device, indices.graphicsFamily, 0, &graphicsQueue);
	vkGetDeviceQueue(device, indices.presentationFamily, 0, &presentationQueue);
}

void LantualVkDevice::GetPhysicalDevice(VkInstance _instance , VkSurfaceKHR _surface )
{
	//Enumerate Physical devices the vkInstance can access
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);

	//cehckk if device is avalaible
	if (deviceCount == 0)
		throw std::runtime_error("can't find GPUs that support Vulkan Instance");

	//get list of physical device
	std::vector<VkPhysicalDevice> deviceList(deviceCount);
	vkEnumeratePhysicalDevices(_instance, &deviceCount, deviceList.data());

	for (const auto& device : deviceList) {
		if (checkDeviceSuitable(device,_surface)) {
			physicalDevice = device;
			break;
		}
	}

}


bool LantualVkDevice::checkDeviceSuitable(VkPhysicalDevice _device , VkSurfaceKHR _surface)
{
	//Information about the device itself 
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(_device, &deviceProperties);

	//information about what device can do (geo shader , tess shader , wide lines ,etc
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(_device, &deviceFeatures);

	QueueFamilyIndices indices = getQueueFamilies(_device,_surface);

	bool extensionSupported = checkDeviceExtensionSupport(_device);

	bool swapChainValid = false;

	if (extensionSupported) {
		SwapChainDetails swapChainDetails = getSwapChainDetails(_device,_surface);
		swapChainValid = !swapChainDetails.presentationModes.empty() && !swapChainDetails.formats.empty();
	}

	return indices.isValid() && extensionSupported && swapChainValid;
}

bool LantualVkDevice::checkDeviceExtensionSupport(VkPhysicalDevice device)
{
	// Get device extension count
	uint32_t extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	// If no extensions found, return failure
	if (extensionCount == 0)
	{
		return false;
	}

	// Populate list of extensions
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, extensions.data());

	// Check for extension
	for (const auto& deviceExtension : deviceExtensions)
	{
		bool hasExtension = false;
		for (const auto& extension : extensions)
		{
			if (strcmp(deviceExtension, extension.extensionName) == 0)
			{
				hasExtension = true;
				break;
			}
		}

		if (!hasExtension)
		{
			return false;
		}
	}

	return true;
}


QueueFamilyIndices LantualVkDevice::getQueueFamilies(VkPhysicalDevice _device , VkSurfaceKHR _surface)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, nullptr);


	std::vector<VkQueueFamilyProperties> queueFamilyList(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, queueFamilyList.data());

	//go through each queue family and check if it has atleast 1 of the required types of queue
	int i = 0;
	for (const auto& queueFamily : queueFamilyList) {
		//first check if queue family has at least 1 queue in that family (could have no queues) + queue can be multiple types defined through bitfield
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i; // if queue family is valid ,ger index
		}

		//checkqueuefamily support presentation
		VkBool32 presentationSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(_device, 1, _surface, &presentationSupport);
		//check if queue is rpresentation type (cna be graphic an presentation )
		if (queueFamily.queueCount > 0 && presentationSupport) {
			indices.presentationFamily = 1;
		}

		if (indices.isValid()) {
			break;
		}

		i++;
	}
	return indices;
}


SwapChainDetails LantualVkDevice::getSwapChainDetails(VkPhysicalDevice _device , VkSurfaceKHR _surface)
{
	SwapChainDetails swapChainDetails;

	//Get surface capabilities for the given surface o nthe given physical device
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_device, _surface, &swapChainDetails.surfaceCapabilities);


	uint32_t formatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(_device, _surface, &formatCount, nullptr);

	if (formatCount != 0) {
		swapChainDetails.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(_device, _surface, &formatCount, swapChainDetails.formats.data());
	}

	//presentaiton modes

	uint32_t presentationCount = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(_device, _surface, &presentationCount, nullptr);

	if (presentationCount != 0) {

		swapChainDetails.presentationModes.resize(presentationCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(_device, _surface, &presentationCount, swapChainDetails.presentationModes.data());
	}
	return swapChainDetails;
}

VkPhysicalDevice LantualVkDevice::GetPhysicalDevice() const
{
	return physicalDevice;
}

VkQueue LantualVkDevice::GetGraphicsQueue() const {
	return graphicsQueue;
}


