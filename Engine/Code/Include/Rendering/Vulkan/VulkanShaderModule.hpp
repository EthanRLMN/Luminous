#pragma once

#include "IShaderModule.hpp"
#include "Struct/VulkanUtilities.hpp"

class VulkanShaderModule : public IShaderModule
{
public:
    bool Create(IDevice* a_device, const std::vector<char>& a_shaders) override;
    void Destroy(IDevice* a_device) override;

    VulkanShaderModule* CastVulkan() override { return this; }
    VkShaderModule GetShaderModule() { return m_shaderModule; }

private:
    VkShaderModule m_shaderModule;

};
