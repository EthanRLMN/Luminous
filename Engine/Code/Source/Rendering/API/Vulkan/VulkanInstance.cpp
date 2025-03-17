#include "Rendering/API/Vulkan/VulkanInstance.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

#include "Rendering/API/Vulkan/VulkanValidationLayer.hpp"

void VulkanInstance::CreateInstance()
{
	if (validationEnabled && !CheckValidationLayerSupport()) {
		std::cout << " validation layer not available";
		return;
	}

	VkApplicationInfo l_applicationInfo{};
	l_applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	l_applicationInfo.pApplicationName = "Luminous";
	l_applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	l_applicationInfo.pEngineName = "Luminous";
	l_applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	l_applicationInfo.apiVersion = VK_API_VERSION_1_3;

	VkInstanceCreateInfo l_createInfo{};
	l_createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	l_createInfo.pApplicationInfo = &l_applicationInfo;

	const char** l_glfwExtensions;
	uint32_t l_glfwExtensionCount{ 0 };
	l_glfwExtensions = glfwGetRequiredInstanceExtensions(&l_glfwExtensionCount);

	std::vector<const char*> instanceExtensions(l_glfwExtensions, l_glfwExtensions + l_glfwExtensionCount);


	if (validationEnabled) {
		instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}


	if (!CheckInstanceExtensionSupport(&instanceExtensions)) {
		std::cout << "vKInstance does not support ";
		return;
	}

	l_createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	l_createInfo.ppEnabledExtensionNames = instanceExtensions.data();


	VkDebugUtilsMessengerCreateInfoEXT l_debugCreateInfo{};

	if (validationEnabled) {
		l_createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		l_createInfo.ppEnabledLayerNames = validationLayers.data();


		l_debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		l_debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		l_debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		l_debugCreateInfo.pfnUserCallback = DebugCallback;

		l_createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&l_debugCreateInfo;
	}
	else {
		l_createInfo.enabledLayerCount = 0;
		l_createInfo.pNext = nullptr;
	}


	VkResult result = vkCreateInstance(&l_createInfo, nullptr, &m_instance);
	if (result != VK_SUCCESS)
		std::cout << "failed to create vulkan instance";
}

void VulkanInstance::Debug()
{
	if (!validationEnabled) return;
	VkDebugUtilsMessengerCreateInfoEXT l_debugCreateInfo{};

	l_debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	l_debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	l_debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	l_debugCreateInfo.pfnUserCallback = DebugCallback;

	if (CreateDebugUtilsMessengerEXT(m_instance, &l_debugCreateInfo, nullptr, &m_callback) != VK_SUCCESS)
		std::cout << "failed to set up debug messenger";
}

void VulkanInstance::Create(IWindow* a_window)
{
	std::cout << "Enter Vulkan Init\n";
	CreateInstance();
	Debug();
}

void VulkanInstance::Destroy()
{
	std::cout << "Destroy Begin\n";
	vkDestroyInstance(m_instance, nullptr);
	std::cout << "Destroy complete\n";
}

bool VulkanInstance::CheckValidationLayerSupport()
{
	uint32_t l_validationLayerCount;
	vkEnumerateInstanceLayerProperties(&l_validationLayerCount, nullptr);

	if (l_validationLayerCount == 0 && validationLayers.size() > 0)
		return false;

	std::vector<VkLayerProperties> l_availableLayers(l_validationLayerCount);
	vkEnumerateInstanceLayerProperties(&l_validationLayerCount, l_availableLayers.data());

	for (const auto& l_validationLayer : validationLayers)
	{
		bool l_hasLayer = false;
		for (const auto& l_availableLayer : l_availableLayers)
		{
			if (strcmp(l_validationLayer, l_availableLayer.layerName) == 0)
			{
				l_hasLayer = true;
				break;
			}
		}

		if (!l_hasLayer)
			return false;
	}
	return true;
}

bool VulkanInstance::CheckInstanceExtensionSupport(std::vector<const char*>* a_checkExtensions)
{
	uint32_t l_extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &l_extensionCount, nullptr);

	std::vector<VkExtensionProperties> l_extensions(l_extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &l_extensionCount, l_extensions.data());

	for (const auto& l_checkExtension : *a_checkExtensions) {
		bool l_hasExtension = false;
		for (const auto& l_extension : l_extensions) {
			if (strcmp(l_checkExtension, l_extension.extensionName)) {
				l_hasExtension = true;
				break;
			}
		}
		if (!l_hasExtension) {
			return false;
		}
	}
	return true;
}
