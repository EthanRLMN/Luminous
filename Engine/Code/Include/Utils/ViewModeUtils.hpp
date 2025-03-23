#pragma once

#include <array>
#include <vulkan/vulkan.h>

// Create custom enum
enum class VIEW_MODE
{
    FILL = 1,
    WIREFRAME = 2
};

// Inline function used to cast our custom enum to the required type
inline VkPolygonMode CastVulkanViewMode(const VIEW_MODE a_type)
{
    const int l_viewTypeIndex = static_cast<int>(a_type);

    // Create a static array inside the function. This allows the array to be created only once no matter where it's used.
    static constexpr std::array<VkPolygonMode, 2> l_vkPolygonMode =
    {
        VK_POLYGON_MODE_FILL,
        VK_POLYGON_MODE_LINE
    };

    return l_vkPolygonMode[l_viewTypeIndex - 1];
}
