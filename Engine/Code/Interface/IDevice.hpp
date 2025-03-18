#pragma once

#include "Logger.hpp"

class VulkanDevice;
class IInstance;
class ISurface;
class IWindow;

class IDevice
{
public:
    virtual ~IDevice() = default;

    virtual void Create(IInstance* a_instance, IWindow* a_window, ISurface* a_surface) = 0;
    virtual void Destroy() = 0;

    virtual VulkanDevice* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan Device : Cast is Wrong!\n");
        return nullptr;
    }
};
