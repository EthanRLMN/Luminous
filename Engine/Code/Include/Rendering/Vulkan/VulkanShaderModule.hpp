#pragma once

#include "IShaderModule.hpp"
#include "Struct/VulkanUtilities.hpp"

class VulkanShaderModule : public IShaderModule
{
public:
    bool Create(IDevice* a_device,const std::string& a_path) override;
    void Destroy(IDevice* a_device) override;

    VulkanShaderModule* CastVulkan() override { return this; }
    VkShaderModule GetShaderModule() { return m_shaderModule; }
    VkPipelineShaderStageCreateInfo CreateStage(VkShaderStageFlagBits a_shaderType);

private:
    VkShaderModule m_shaderModule;

};
