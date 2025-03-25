#include "Logger.hpp"

#include "IInstance.hpp"
#include "IWindow.hpp"

#include "Core/GLFW/GLFWWindow.hpp"

#include "Rendering/Vulkan/VulkanSurface.hpp"
#include "Rendering/Vulkan/VulkanInstance.hpp"

void VulkanSurface::Create(IInstance* a_instance, IWindow* a_window)
{
    const VkResult l_result = glfwCreateWindowSurface(a_instance->CastVulkan()->GetInstance(), a_window->CastGLFW()->GetGLFWWindow(), nullptr, &m_surface);

    if (l_result != VK_SUCCESS)
        DEBUG_LOG_ERROR("Vulkan Surface : Failed to create Surface!\n");
}

void VulkanSurface::Destroy(IInstance* a_instance)
{
    DEBUG_LOG_INFO("Vulkan Surface : Surface has been destroyed!\n");
}
