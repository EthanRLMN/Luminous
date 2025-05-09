#pragma once

#include "Logger.hpp"

class VulkanInstance;
class IWindow;

class IInstance
{
public:
    virtual ~IInstance() = default;

    virtual void Create() = 0;
    virtual void Destroy() = 0;

    virtual VulkanInstance* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan Instance : Cast is Wrong!\n");
        return nullptr;
    }
};
