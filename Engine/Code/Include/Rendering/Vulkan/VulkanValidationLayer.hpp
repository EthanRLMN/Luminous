#pragma once
#include <vector>
#include <array>
#include <vulkan/vulkan.h>

#include "Logger.hpp"

class ValidationLayer
{
public:
    static constexpr bool ValidationLayersEnabled{ true };
    static constexpr std::array<const char*, 2> ValidationLayers{ "VK_LAYER_KHRONOS_validation", "VK_LAYER_LUNARG_monitor" };

    static VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT a_messageSeverity, VkDebugUtilsMessageTypeFlagsEXT a_messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* a_pCallbackData, void* a_pUserData);
    static VkResult CreateDebugUtilsMessengerEXT(const VkInstance& a_instance, const VkDebugUtilsMessengerCreateInfoEXT* a_pCreateInfo, const VkAllocationCallbacks* a_pAllocator, VkDebugUtilsMessengerEXT* a_pDebugMessenger);
    static void DestroyDebugReportCallbackEXT(const VkInstance& a_instance, const VkDebugReportCallbackEXT& a_callback, const VkAllocationCallbacks* a_pAllocator);
};