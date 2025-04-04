#pragma once

#include <vector>
#include "Logger.hpp"

class IDevice;
class VulkanShaderModule;

class IShaderModule
{
public:
	
	IShaderModule() = default;
    ~IShaderModule() = default;

	virtual bool Create(IDevice* a_device, const std::vector<char>& a_shaders) = 0;
    virtual void Destroy() = 0;

	virtual VulkanShaderModule* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan ShaderModule : Cast is Wrong!\n");
        return nullptr;
    };

};
