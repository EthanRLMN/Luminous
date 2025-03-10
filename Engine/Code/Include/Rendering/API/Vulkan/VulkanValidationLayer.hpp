#pragma once

#include <cstdio>
#include <vector>
#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_core.h>

constexpr bool validationEnabled = true;

const std::vector<const char*> validationLayers =
{
	"VK_LAYER_KHRONOS_validation"
	//VK_LAYER_LUNARG_standard_validation doesn't work for me :[
};

// Callback function for validation debugging (will be called when validation information record)
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugReportFlagsEXT flags, // Type of error
	VkDebugReportObjectTypeEXT objType, // Type of object causing error
	uint64_t obj, // ID of object
	size_t location,
	int32_t code,
	const char* layerPrefix,
	const char* message, // Validation Information
	void* userData)
{
	// If validation ERROR, then output error and return failure
	if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
	{
		printf("VALIDATION ERROR: %s\n", message);
		return VK_TRUE;
	}

	// If validation WARNING, then output warning and return okay
	if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT)
	{
		printf("VALIDATION WARNING: %s\n", message);
		return VK_FALSE;
	}

	return VK_FALSE;
}

static VkResult CreateDebugReportCallbackEXT(const VkInstance a_instance,
                                             const VkDebugReportCallbackCreateInfoEXT* a_pCreateInfo,
                                             const VkAllocationCallbacks* a_pAllocator,
                                             VkDebugReportCallbackEXT* a_pCallback)
{
	// vkGetInstanceProcAddr returns a function pointer to the requested function in the requested instance
	// resulting function is cast as a function pointer with the header of "vkCreateDebugReportCallbackEXT"
	const auto l_func = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(
		vkGetInstanceProcAddr(a_instance, "vkCreateDebugReportCallbackEXT"));

	// If function was found, executre if with given data and return result, otherwise, return error
	if (l_func != nullptr)
		return l_func(a_instance, a_pCreateInfo, a_pAllocator, a_pCallback);

	return VK_ERROR_EXTENSION_NOT_PRESENT;
}

static void DestroyDebugReportCallbackEXT(const VkInstance a_instance, const VkDebugReportCallbackEXT a_callback,
                                          const VkAllocationCallbacks* a_pAllocator)
{
	// get function pointer to requested function, then cast to function pointer for vkDestroyDebugReportCallbackEXT
	const auto l_func = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(
		vkGetInstanceProcAddr(a_instance, "vkDestroyDebugReportCallbackEXT"));

	// If function found, execute
	if (l_func != nullptr)
	{
		l_func(a_instance, a_callback, a_pAllocator);
	}
}
