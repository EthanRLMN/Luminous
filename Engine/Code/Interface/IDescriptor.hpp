#pragma once
#include "Logger.hpp"

class VulkanDescriptor;
class IDevice;
class IDescriptorSetLayout;
class ITexture;

class IDescriptor
{
public:
    virtual ~IDescriptor() = default;

    virtual void Create(IDevice* a_device, IDescriptorSetLayout* a_descriptionSetLayout, ITexture* a_texture) = 0;
    virtual void Destroy() = 0;

    virtual VulkanDescriptor* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan Descriptor : Cast is Wrong!\n");
        return nullptr;
    }
};
