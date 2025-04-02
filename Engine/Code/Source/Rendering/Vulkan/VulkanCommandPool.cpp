#include "Rendering/Vulkan/VulkanCommandPool.hpp"

#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanSurface.hpp"


void VulkanCommandPool::Create(IDevice* a_device, ISurface* a_surface)
{
    const QueueFamilyIndices l_queueFamilyIndices = a_device->CastVulkan()->GetQueueFamilies(a_device->CastVulkan()->GetPhysicalDevice(), a_surface->CastVulkan()->GetSurface());
    VkCommandPoolCreateInfo l_poolInfo = { VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
    l_poolInfo.queueFamilyIndex = l_queueFamilyIndices.graphicsFamily;
    l_poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    const VkResult l_result = vkCreateCommandPool(a_device->CastVulkan()->GetDevice(), &l_poolInfo, nullptr, &m_graphicsCommandPool);
    if (l_result != VK_SUCCESS)
        DEBUG_LOG_ERROR("Vulkan CommandPool : Failed to create CommandPool!\n");

    DEBUG_LOG_INFO("Vulkan CommandPool : Create CommandPool!\n");
}

void VulkanCommandPool::Destroy(IDevice* a_device)
{
    vkDestroyCommandPool(a_device->CastVulkan()->GetDevice(), m_graphicsCommandPool, nullptr);
    DEBUG_LOG_INFO("Vulkan CommandPool : Destroy CommandPool!\n");
}
