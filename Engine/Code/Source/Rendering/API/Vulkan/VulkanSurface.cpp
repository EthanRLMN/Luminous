#include "Rendering/API/Vulkan/VulkanSurface.hpp"

#include <iostream>

#include "IInstance.hpp"
#include "IWindow.hpp"
#include "Rendering/API/Vulkan/VulkanInstance.hpp"
#include "Rendering/API/Vulkan/VulkanWindow.hpp"

void VulkanSurface::Create(IInstance* a_instance, IWindow* a_window)
{
    VkResult l_result = glfwCreateWindowSurface(a_instance->CastVulkan()->GetInstance(), a_window->CastVulkan()->GetGLFWWindow(), nullptr, &m_surface);
    if (l_result != VK_SUCCESS) {
        std::cout << "failed to create Surface";
    }
}

void VulkanSurface::Destroy(IInstance* a_instance)
{
    std::cout << "Destroy Surface\n";
}
