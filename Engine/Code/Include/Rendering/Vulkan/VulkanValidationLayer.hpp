#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "Logger.hpp"

constexpr bool validationEnabled = true;

const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation", "VK_LAYER_LUNARG_monitor" };

// Callback function for validation debugging (will be called when validation information record)
static VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT a_messageSeverity, VkDebugUtilsMessageTypeFlagsEXT a_messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* a_pCallbackData, void* a_pUserData)
{
    const char* l_messageTypeStr { "" };
    if (a_messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
        l_messageTypeStr = "General";
    else if (a_messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
        l_messageTypeStr = "Validation";
    else if (a_messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
        l_messageTypeStr = "Performance";

    const char* l_messageIdName = a_pCallbackData->pMessageIdName ? a_pCallbackData->pMessageIdName : "Unknown";
    switch (a_messageSeverity)
    {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            DEBUG_LOG_VERBOSE("[{}] [{}] - {}\n", l_messageTypeStr, l_messageIdName, a_pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            DEBUG_LOG_INFO("[{}] [{}] - {}\n", l_messageTypeStr, l_messageIdName, a_pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            DEBUG_LOG_WARNING("[{}] [{}] - {}\n", l_messageTypeStr, l_messageIdName, a_pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            DEBUG_LOG_ERROR("[{}] [{}] - {}\n", l_messageTypeStr, l_messageIdName, a_pCallbackData->pMessage);
            break;
        default:
            DEBUG_LOG_INFO("[{}] [{}] - {}\n", l_messageTypeStr, l_messageIdName, a_pCallbackData->pMessage);
            break;
    }
    return VK_FALSE;
}


static VkResult CreateDebugUtilsMessengerEXT(const VkInstance& a_instance, const VkDebugUtilsMessengerCreateInfoEXT* a_pCreateInfo, const VkAllocationCallbacks* a_pAllocator, VkDebugUtilsMessengerEXT* a_pDebugMessenger)
{
	const auto l_func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(a_instance, "vkCreateDebugUtilsMessengerEXT"));

	if (l_func == nullptr)
		return VK_ERROR_EXTENSION_NOT_PRESENT;

	return l_func(a_instance, a_pCreateInfo, a_pAllocator, a_pDebugMessenger);
}


static void DestroyDebugReportCallbackEXT(const VkInstance& a_instance, const VkDebugReportCallbackEXT& a_callback, const VkAllocationCallbacks* a_pAllocator)
{
	const auto l_func = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(a_instance, "vkDestroyDebugReportCallbackEXT"));

	if (l_func != nullptr)
		l_func(a_instance, a_callback, a_pAllocator);
}
