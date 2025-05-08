#pragma once

#include "Logger.hpp"
#include "ResourceManager/Resource.hpp"

class VulkanShader;

class IShader : public IResource
{
public:
    IShader() = default;

    bool Create(const IResourceParams& a_params) override { static_cast<void>(a_params); return false; }
    void Destroy(IDevice* a_device) override { static_cast<void>(a_device); }

    virtual VulkanShader* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan Shader : Cast is Wrong!\n");
        return nullptr;
    }
};
