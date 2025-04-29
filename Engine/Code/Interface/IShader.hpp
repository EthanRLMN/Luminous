#pragma once

#include "Logger.hpp"
#include "ResourceManager/Resource.hpp"

class VulkanShader;

class IShader : public IResource
{
public:
    IShader() = default;

    bool Create(IResourceManager* a_manager, const IResourceParams& a_params) override { return false; };
    void Destroy(IDevice* a_device) override {};

    virtual VulkanShader* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan Shader : Cast is Wrong!\n");
        return nullptr;
    }
};
