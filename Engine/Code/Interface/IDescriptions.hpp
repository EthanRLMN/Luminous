#pragma once

#include "Logger.hpp"

class VulkanDescriptor;
class IDevice;

class IDescriptor
{
public:
    virtual ~IDescriptor() = default;

    virtual void Create(IDevice* a_device) = 0;
    virtual void Destroy() = 0;

    virtual VulkanDescriptor* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan Descriptor : Cast is Wrong!\n");
        return nullptr;
    }
};
