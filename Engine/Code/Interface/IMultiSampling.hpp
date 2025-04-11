
#pragma once

#include "Logger.hpp"

class VulkanMultiSampling;
class IDevice;




class IMultiSampling
{
public:
    virtual ~IMultiSampling() = default;

    virtual void Create(IDevice* a_device) = 0;
    virtual void Destroy(IDevice* a_device) = 0;

    virtual VulkanMultiSampling* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan MultiSampling : Cast is Wrong!\n");
        return nullptr;
    }
};
