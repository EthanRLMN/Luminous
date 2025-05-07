#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "Logger.hpp"

namespace ValidationLayer
{
    static constexpr bool ValidationLayersEnabled{ true };

    const std::vector<const char*> m_validationLayers{ "VK_LAYER_KHRONOS_validation", "VK_LAYER_LUNARG_monitor" };

    // Callback function for validation debugging (will be called when validation information record)
    static VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT a_messageSeverity, VkDebugUtilsMessageTypeFlagsEXT a_messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* a_pCallbackData, void* a_pUserData);
    static VkResult CreateDebugUtilsMessengerEXT(const VkInstance& a_instance, const VkDebugUtilsMessengerCreateInfoEXT* a_pCreateInfo, const VkAllocationCallbacks* a_pAllocator, VkDebugUtilsMessengerEXT* a_pDebugMessenger);
    static void DestroyDebugReportCallbackEXT(const VkInstance& a_instance, const VkDebugReportCallbackEXT& a_callback, const VkAllocationCallbacks* a_pAllocator);
}