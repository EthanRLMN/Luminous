#pragma once

#include <span>

#include "IPipeline.hpp"
#include "vulkan/vulkan.h"


class IRenderPass;

class VulkanPipeline final : public IPipeline
{
public:
    void Create(IDevice* a_device, IRenderPass* a_renderPass, IDescriptorSetLayout* a_descriptionSetLayout) override;
	void Destroy(IDevice* a_device) override;

	[[nodiscard]] VkPipeline GetGraphicsPipeline() const { return m_graphicsPipeline; }
	[[nodiscard]] VkPipelineLayout GetPipelineLayout() const { return m_pipelineLayout; };

	VulkanPipeline* CastVulkan() override { return this; }


private:
    static void VertexStageCreation(VkPipelineShaderStageCreateInfo& a_vertexShaderCreateInfo, const VkShaderModule& a_vertexShaderModule);
    static void FragmentStageCreation(VkPipelineShaderStageCreateInfo& a_fragmentShaderCreateInfo, const VkShaderModule& a_fragmentShaderModule);
    static void BindShaderAttributes(VkVertexInputBindingDescription& a_bindingDescription, std::array<VkVertexInputAttributeDescription, 3> a_attributeDescriptions, VkPipelineVertexInputStateCreateInfo& a_vertexInputCreateInfo);
    static void SetupInputAssemblyState(VkPipelineInputAssemblyStateCreateInfo& a_inputAssembly);
    static void SetupViewportState(VkPipelineViewportStateCreateInfo& a_viewportCreateInfo);
    static void SetupRasterizerCreationInfo(VkPipelineRasterizationStateCreateInfo& a_rasterizerCreateInfo);
    static void SetupSamplingState(VkPipelineMultisampleStateCreateInfo& a_multisamplingCreateInfo, VkSampleCountFlagBits a_sampleCount);
    static void SetupDepthStencilState(VkPipelineDepthStencilStateCreateInfo& a_depthStencilCreateInfo);
    static void SetupColorBlendAttachmentState(VkPipelineColorBlendAttachmentState& a_colorBlendAttachment);
    static void SetupColorBlendingState(VkPipelineColorBlendStateCreateInfo& a_colorBlendingCreateInfo, const VkPipelineColorBlendAttachmentState& a_colorBlendAttachment);
    static void SetupDynamicStates(const std::array<VkDynamicState, 2>& a_dynamicStates, VkPipelineDynamicStateCreateInfo& a_dynamicStateCreationInfo);
    void SetupPushConstants(VkPipelineLayoutCreateInfo& a_layout, VkPushConstantRange& a_pushConstant);
    void SetupDescriptorSetLayout(const std::vector<VkDescriptorSetLayout> a_descriptorSetLayouts, VkPipelineLayoutCreateInfo& a_pipelineLayoutInfo, const VkDevice a_device);
    void PushPipelineInfo(VkPipeline& a_pipeline, VkGraphicsPipelineCreateInfo& a_pipelineCreateInfo, const std::span<VkPipelineShaderStageCreateInfo>& a_shaderStages, const VkPipelineVertexInputStateCreateInfo& a_vertexInputCreateInfo, const VkPipelineInputAssemblyStateCreateInfo& a_inputAssembly, const VkPipelineViewportStateCreateInfo& a_viewportStateCreateInfo, const VkPipelineRasterizationStateCreateInfo& a_rasterizerCreateInfo, const VkPipelineMultisampleStateCreateInfo& a_multisamplingCreateInfo, const VkPipelineDepthStencilStateCreateInfo& a_depthStencil, const VkPipelineColorBlendStateCreateInfo& a_colorBlending, const VkPipelineDynamicStateCreateInfo& a_dynamicStateCreationInfo, const VkRenderPass& a_renderPass, const VkDevice& a_device);
	VkPipeline m_graphicsPipeline { nullptr };

	VkPipelineLayout m_pipelineLayout { nullptr };
};