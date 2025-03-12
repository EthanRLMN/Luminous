#include "Rendering/API/Vulkan/VulkanSurface.hpp"

#include <iostream>

#include "IInstance.hpp"
#include "IWindow.hpp"
#include "Rendering/API/Vulkan/VulkanInstance.hpp"
#include "Rendering/API/Vulkan/VulkanWindow.hpp"

void VulkanSurface::Create(IInstance* a_instance, EWindow* a_window)
{
    std::cout << "Create Surface\n";

    if (const VkResult l_result = glfwCreateWindowSurface(a_instance->CastVulkan()->GetInstance(), a_window->CastVulkan()->GetGLFWWindow(), nullptr,
                                                          &m_surface); l_result != VK_SUCCESS)
    {
        std::cerr << "Failed to create surface, error code: " << l_result << "\n";
        throw std::runtime_error("failed to create surface");
    }
    std::cout << "Finish Create Surface\n";
}

void VulkanSurface::Destroy(IInstance* a_instance)
{
    std::cout << "Destroy Surface\n";
}
