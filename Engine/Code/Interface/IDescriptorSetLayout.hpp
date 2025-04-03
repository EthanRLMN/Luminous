#pragma once
#include "Logger.hpp"

class VulkanDescriptorSetLayout;
class IDevice;

class IDescriptorSetLayout
{
public:
    virtual ~IDescriptorSetLayout() = default;

    virtual void Create(IDevice* a_device) = 0;
    virtual void Destroy(IDevice* a_device) = 0;

    virtual VulkanDescriptorSetLayout* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan DescriptorSetLayout : Cast is Wrong!\n");
        return nullptr;
    }
};
