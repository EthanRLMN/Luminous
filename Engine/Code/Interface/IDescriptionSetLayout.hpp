#pragma once
#include "Logger.hpp"

class VulkanDescriptionSetLayout;
class IDevice;

class IDescriptionSetLayout
{
public:
    virtual ~IDescriptionSetLayout() = default;

    virtual void Create(IDevice* a_device) = 0;
    virtual void Destroy() = 0;

    virtual VulkanDescriptionSetLayout* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan DescriptorSetLayout : Cast is Wrong!\n");
        return nullptr;
    }
};
