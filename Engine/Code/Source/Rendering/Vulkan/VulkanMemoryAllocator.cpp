#include "IDevice.hpp"
#include "IInstance.hpp"

#include "Rendering/Vulkan/VulkanMemoryAllocator.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanInstance.hpp"

void VulkanMemoryAllocator::Init(IInstance* a_instance, IDevice* a_device)
{
    const VulkanDevice* l_vulkanDevice = a_device->CastVulkan();

    VmaAllocatorCreateInfo allocatorInfo = {};
    allocatorInfo.physicalDevice = l_vulkanDevice->GetPhysicalDevice();
    allocatorInfo.device = l_vulkanDevice->GetDevice();
    allocatorInfo.instance = a_instance->CastVulkan()->GetInstance();

    vmaCreateAllocator(&allocatorInfo, &m_memAllocator);
}
