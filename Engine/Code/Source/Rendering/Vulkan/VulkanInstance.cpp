#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Rendering/Vulkan/VulkanInstance.hpp"
#include "Rendering/Vulkan/VulkanValidationLayer.hpp"


void VulkanInstance::CreateInstance()
{
	if (!CheckValidationLayerSupport())
	{
		DEBUG_LOG_ERROR("Vulkan Instance : Validation Layer support is not available!\n");
		return;
	}

	VkApplicationInfo l_applicationInfo { };
	SetupApplicationInfo(l_applicationInfo);

	VkInstanceCreateInfo l_createInfo {
	    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
	    .pNext = nullptr,
	    .flags = 0,
	    .pApplicationInfo = &l_applicationInfo,
	    .enabledLayerCount = 0,
	    .ppEnabledLayerNames = nullptr,
	    .enabledExtensionCount = 0,
	    .ppEnabledExtensionNames = nullptr,
	};

	SetupValidationLayers(l_createInfo);
}


void VulkanInstance::Debug()
{
	VkDebugUtilsMessengerCreateInfoEXT l_debugCreateInfo { };
	SetupDebugCreateInfo(l_debugCreateInfo);

	if (ValidationLayer::CreateDebugUtilsMessengerEXT(m_instance, &l_debugCreateInfo, nullptr, &m_debugMessenger) != VK_SUCCESS)
		DEBUG_LOG_ERROR("Vulkan Instance : Failed to setup Debug Messenger!\n");
}


void VulkanInstance::SetupValidationLayers(VkInstanceCreateInfo& a_createInfo)
{
	uint32_t l_glfwExtensionCount { 0 };
	const char** l_glfwExtensions = glfwGetRequiredInstanceExtensions(&l_glfwExtensionCount);

	std::vector<const char*> l_instanceExtensions(l_glfwExtensions, l_glfwExtensions + l_glfwExtensionCount);
	if (ValidationLayer::ValidationLayersEnabled)
		l_instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	if (!CheckInstanceExtensionSupport(&l_instanceExtensions))
	{
		DEBUG_LOG_ERROR("Vulkan Instance : Instance extensions is not supported!\n");
		return;
	}

	a_createInfo.enabledExtensionCount = static_cast<uint32_t>(l_instanceExtensions.size());
	a_createInfo.ppEnabledExtensionNames = l_instanceExtensions.data();

	if (ValidationLayer::ValidationLayersEnabled)
	{
		a_createInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayer::m_validationLayers.size());
		a_createInfo.ppEnabledLayerNames = ValidationLayer::m_validationLayers.data();

		VkDebugUtilsMessengerCreateInfoEXT l_debugCreateInfo { };
		SetupDebugCreateInfo(l_debugCreateInfo);

		a_createInfo.pNext = static_cast<VkDebugUtilsMessengerCreateInfoEXT*>(&l_debugCreateInfo);
	}

	const VkResult l_result = vkCreateInstance(&a_createInfo, nullptr, &m_instance);
	if (l_result != VK_SUCCESS)
		DEBUG_LOG_ERROR("Vulkan Instance : Failed to create Vulkan Instance!\n");
}


void VulkanInstance::SetupApplicationInfo(VkApplicationInfo& a_applicationInfo)
{
    a_applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	a_applicationInfo.pApplicationName = "Luminous";
	a_applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	a_applicationInfo.pEngineName = "Luminous";
	a_applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	a_applicationInfo.apiVersion = VK_API_VERSION_1_4;
}


void VulkanInstance::SetupDebugCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& a_createInfo)
{
    a_createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	a_createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	a_createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	a_createInfo.pfnUserCallback = ValidationLayer::DebugCallback;
    a_createInfo.pNext = nullptr;
}


void VulkanInstance::Create()
{
	CreateInstance();
	Debug();

	DEBUG_LOG_INFO("Vulkan Instance : Instance created!\n");
}


void VulkanInstance::Destroy()
{
	if (ValidationLayer::ValidationLayersEnabled)
	{
		if (m_debugMessenger)
		{
			const PFN_vkDestroyDebugUtilsMessengerEXT l_destroyMessenger = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT"));
			if (l_destroyMessenger)
				l_destroyMessenger(m_instance, m_debugMessenger, nullptr);
		}
	}

	if (m_instance)
		vkDestroyInstance(m_instance, nullptr);

	DEBUG_LOG_INFO("Vulkan Instance : Instance Deleted!\n");
}


bool VulkanInstance::CheckValidationLayerSupport()
{
	uint32_t l_validationLayerCount { 0 };
	vkEnumerateInstanceLayerProperties(&l_validationLayerCount, nullptr);

	if (l_validationLayerCount == 0 && !ValidationLayer::m_validationLayers.empty()) return false;

	std::vector<VkLayerProperties> l_availableLayers(l_validationLayerCount);
	vkEnumerateInstanceLayerProperties(&l_validationLayerCount, l_availableLayers.data());

	for (const auto& l_layer : ValidationLayer::m_validationLayers)
	{
		bool l_hasLayer = false;
		for (const auto& l_availableLayer : l_availableLayers)
		{
			if (strcmp(l_layer, l_availableLayer.layerName) == 0)
			{
				l_hasLayer = true;
				break;
			}
		}

		if (!l_hasLayer) return false;
	}
	return true;
}


bool VulkanInstance::CheckInstanceExtensionSupport(const std::vector<const char*>* a_checkExtensions)
{
	uint32_t l_extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &l_extensionCount, nullptr);

	std::vector<VkExtensionProperties> l_extensions(l_extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &l_extensionCount, l_extensions.data());

	for (const auto& l_checkExtension : *a_checkExtensions)
	{
		bool l_hasExtension = false;
		for (const auto& l_extension : l_extensions)
		{
			if (strcmp(l_checkExtension, l_extension.extensionName) != 0)
			{
				l_hasExtension = true;
				break;
			}
		}

		if (!l_hasExtension) return false;
	}
	return true;
}
