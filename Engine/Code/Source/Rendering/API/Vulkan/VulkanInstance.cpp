#include "Rendering/API/Vulkan/VulkanInstance.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

#include "Rendering/API/Vulkan/VulkanValidationLayer.hpp"

void VulkanInstance::VkCreateInstance()
{
	//informaton du programme qu'on fait 
	VkApplicationInfo l_applicationInfo = {};
	l_applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	l_applicationInfo.pApplicationName = "VulkanRendering";
	l_applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	l_applicationInfo.pEngineName = "NoEngine";
	l_applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	l_applicationInfo.apiVersion = VK_API_VERSION_1_0;

	//create information for our vkInstance 
	VkInstanceCreateInfo l_createInfo = {};
	l_createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	l_createInfo.pApplicationInfo = &l_applicationInfo;

	//Create list to hold inctance extensions
	std::vector<const char*> l_instanceExtensions = std::vector<const char*>();

	//Set up extensions Instance will use
	uint32_t l_glfwExtensionCount = 0; //GLFW may require multiple extensions
	//Extensions passed as array of cstrings , so need pointer (the array ) to pointer (the cstring)

	const char** l_glfwExtensions = glfwGetRequiredInstanceExtensions(&l_glfwExtensionCount); //get glfw extensions

	for (size_t i = 0; i < l_glfwExtensionCount; i++)
		l_instanceExtensions.push_back(l_glfwExtensions[i]);

	if (validationEnabled)
		l_instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

	l_createInfo.enabledExtensionCount = static_cast<uint32_t>(l_instanceExtensions.size());
	l_createInfo.ppEnabledExtensionNames = l_instanceExtensions.data();

	//set up validation layers that instance will use
	l_createInfo.enabledLayerCount = 0;
	l_createInfo.ppEnabledLayerNames = nullptr;

	if (validationEnabled)
	{
		l_createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		l_createInfo.ppEnabledLayerNames = validationLayers.data();
	} else
	{
		l_createInfo.enabledLayerCount = 0;
		l_createInfo.ppEnabledLayerNames = nullptr;
	}

	//Create Instance
	//vkallocationcallback et pour g�r� la memoire , a implement� plus tard

	if (VkResult l_result = vkCreateInstance(&l_createInfo, nullptr, &m_instance); l_result != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create vulkan instance");
	}
	std::cout << "Finish VkInstance\n";
}

void VulkanInstance::VkDebugCallback()
{
	// Only create callback if validation is enabled
	if constexpr (!validationEnabled) return;

	// Retrieve the function pointer for vkCreateDebugReportCallbackEXT
	const auto l_func = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(
		vkGetInstanceProcAddr(m_instance, "vkCreateDebugReportCallbackEXT"));

	if (!l_func)
	{
		throw std::runtime_error("Could not load vkCreateDebugReportCallbackEXT!");
	}

	// Create the callback information struct
	VkDebugReportCallbackCreateInfoEXT l_callbackCreateInfo = {};
	l_callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	l_callbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	l_callbackCreateInfo.pfnCallback = debugCallback; // Set the callback function

	// Create the callback

	if (const VkResult l_result = l_func(m_instance, &l_callbackCreateInfo, nullptr, &m_callback);
		l_result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Debug Callback!");
	}
}


void VulkanInstance::Create(Window* a_window)
{
	std::cout << "Enter Vulkan Init\n";
	VkCreateInstance();
	VkDebugCallback();
}

void VulkanInstance::Destroy()
{
	std::cout << "Destroy Begin\n";
	vkDestroyInstance(m_instance, nullptr);
	std::cout << "Destroy complete\n";
}
