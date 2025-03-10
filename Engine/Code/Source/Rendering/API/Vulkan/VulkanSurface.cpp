#include "Rendering/API/Vulkan/VulkanSurface.hpp"

#include <iostream>

#include "Rendering/IInstance.hpp"
#include "Rendering/Window.hpp"
#include "Rendering/API/Vulkan/VulkanInstance.hpp"

void VulkanSurface::Create(IInstance* a_instance, Window* a_window)
{
    std::cout << "Create Surface\n";

    if (const VkResult l_result = glfwCreateWindowSurface(a_instance->CastVulkan()->GetInstance(), a_window->m_Window, nullptr,
                                                          &m_surface); l_result != VK_SUCCESS)
    {
        std::cerr << "Failed to create surface, error code: " << l_result << "\n";
        throw std::runtime_error("failed to create surface");
    }
    std::cout << "Finish Create Surface\n";
}

void VulkanSurface::Destroy(IInstance* a_instance)
{
    std::cout << "Destroy Surface\n" << a_instance;
}
