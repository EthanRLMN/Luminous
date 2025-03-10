#include "LantualVKInstance.h"


void LantualVKInstance::VkCreateInstance()
{

	//informaton du programme qu'on fait 
	VkApplicationInfo applicationInfo = {};
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.pApplicationName = "VulkanRendering";
	applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.pEngineName = "NoEngine";
	applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.apiVersion = VK_API_VERSION_1_0;

	//create information for our vkInstance 
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &applicationInfo;

	//Create list to hold inctance extensions
	std::vector<const char*> instanceExtensions = std::vector<const char*>();

	//Set up extensions Instance will use
	uint32_t glfwExtensionCount = 0; //GLFW may require multiple extensions
	const char** glfwExtensions; //Extensions passed as array of cstrings , so need pointer (the array ) to pointer (the cstring)

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);//get glfw extensions

	for (size_t i = 0; i < glfwExtensionCount; i++)
		instanceExtensions.push_back(glfwExtensions[i]);

	if (validationEnabled)
		instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

	createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	createInfo.ppEnabledExtensionNames = instanceExtensions.data();

	//set up validation layers that instance will use
	createInfo.enabledLayerCount = 0;
	createInfo.ppEnabledLayerNames = nullptr;

	if (validationEnabled) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
		createInfo.ppEnabledLayerNames = nullptr;
	}

	//Create Instance
	VkResult result = vkCreateInstance(&createInfo, nullptr, &instance); //vkallocationcallback et pour géré la memoire , a implementé plus tard

	if (result != VK_SUCCESS) { throw std::runtime_error("failed to create vulkan instance"); }
	std::cout << "Finish VkInstance" <<std::endl;
}

void LantualVKInstance::VkDebugCallback()
{
	// Only create callback if validation is enabled
	if (!validationEnabled) return;

	// Retrieve the function pointer for vkCreateDebugReportCallbackEXT
	auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (!func) {
		throw std::runtime_error("Could not load vkCreateDebugReportCallbackEXT!");
	}

	// Create the callback information struct
	VkDebugReportCallbackCreateInfoEXT callbackCreateInfo = {};
	callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	callbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	callbackCreateInfo.pfnCallback = debugCallback;  // Set the callback function

	// Create the callback
	VkResult result = func(instance, &callbackCreateInfo, nullptr, &callback);

	if (result != VK_SUCCESS) {
		throw std::runtime_error("Failed to create Debug Callback!");
	}
}


void LantualVKInstance::Create(Window* _window)
{
	std::cout << "Enter Vulkan Init" << std::endl;
	VkCreateInstance();
	VkDebugCallback();

}

void LantualVKInstance::Destroy()
{
	std::cout << "Destroy Begin" << std::endl;
	vkDestroyInstance(instance, nullptr);
	std::cout << "Destroy complete" << std::endl;
}
