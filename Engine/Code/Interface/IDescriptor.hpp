#pragma once

#include "Logger.hpp"

class VulkanDescriptor;
class IDevice;
class IDescriptorSetLayout;
class ITexture;
class IBuffer;


class IDescriptor
{
public:
    virtual ~IDescriptor() = default;

    virtual void Create(IDevice* a_device, IDescriptorSetLayout* a_descriptionSetLayout, ITexture* a_texture, IBuffer* a_buffer) = 0;
    virtual void Destroy(IDevice* a_device) = 0;
    

    virtual VulkanDescriptor* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan Descriptor : Cast is Wrong!\n");
        return nullptr;
    }
};
