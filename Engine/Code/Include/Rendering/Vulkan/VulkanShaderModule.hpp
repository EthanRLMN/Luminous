#pragma once

#include "IShaderModule.hpp"
#include "Struct/VulkanUtilities.hpp"

class VulkanShaderModule final : public IShaderModule
{
public:
    bool Create(IDevice* a_device,const std::string& a_path) override;
    void Destroy(IDevice* a_device) override;

    VulkanShaderModule* CastVulkan() override { return this; }
    [[nodiscard]] VkShaderModule GetShaderModule() const { return m_shaderModule; }
    [[nodiscard]] VkPipelineShaderStageCreateInfo CreateStage(VkShaderStageFlagBits a_shaderType) const;
    static void BindShader(VkVertexInputBindingDescription& a_bindingDescription, std::array<VkVertexInputAttributeDescription, 3> a_attributeDescriptions, VkPipelineVertexInputStateCreateInfo& a_vertexInputCreateInfo);

private:
    VkShaderModule m_shaderModule { nullptr };
};
