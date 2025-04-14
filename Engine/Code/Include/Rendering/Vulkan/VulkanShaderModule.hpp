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
    void BindShader(VkVertexInputBindingDescription& a_bindingDescription, std::array<VkVertexInputAttributeDescription, 3> a_attributeDescriptions, VkPipelineVertexInputStateCreateInfo& a_vertexInputCreateInfo);

private:
    VkShaderModule m_shaderModule;

};
