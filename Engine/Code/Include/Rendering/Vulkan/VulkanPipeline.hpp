#pragma once

#include <span>
#include <vector>

#include "IPipeline.hpp"
#include "vulkan/vulkan.h"
#include "ResourceManager/ResourceManager.hpp"
#include "Rendering/Vulkan/VulkanShader.hpp"


class VulkanPipeline final : public IPipeline
{
public:
    void Create(IDevice* a_device, IRenderPass* a_renderPass, IDescriptorSetLayout* a_descriptionSetLayout, IResourceManager* a_resourceManager) override;
	void Destroy(IDevice* a_device) override;

	[[nodiscard]] VkPipeline GetGraphicsPipeline() const { return m_graphicsPipeline; }
	[[nodiscard]] VkPipelineLayout GetPipelineLayout() const { return m_pipelineLayout; };

	VulkanPipeline* CastVulkan() override { return this; }


private:
	void VertexStageCreation(VkPipelineShaderStageCreateInfo& a_vertexShaderCreateInfo, const VkShaderModule& a_vertexShaderModule);
	void FragmentStageCreation(VkPipelineShaderStageCreateInfo& a_fragmentShaderCreateInfo, const VkShaderModule& a_fragmentShaderModule);
	void BindShaderAttributes(VkVertexInputBindingDescription& a_bindingDescription, std::array<VkVertexInputAttributeDescription, 3> a_attributeDescriptions, VkPipelineVertexInputStateCreateInfo& a_vertexInputCreateInfo);
	void SetupInputAssemblyState(VkPipelineInputAssemblyStateCreateInfo& a_inputAssembly);
	void SetupViewportState(VkPipelineViewportStateCreateInfo& a_viewportCreateInfo);
	void SetupRasterizerCreationInfo(VkPipelineRasterizationStateCreateInfo& a_rasterizerCreateInfo);
	void SetupMultisamplingState(VkPipelineMultisampleStateCreateInfo& a_multisamplingCreateInfo);
	void SetupDepthStencilState(VkPipelineDepthStencilStateCreateInfo& a_depthStencilCreateInfo);
	void SetupColorBlendAttachmentState(VkPipelineColorBlendAttachmentState& a_colorBlendAttachment);
	void SetupColorBlendingState(VkPipelineColorBlendStateCreateInfo& a_colorBlendingCreateInfo, const VkPipelineColorBlendAttachmentState& a_colorBlendAttachment);
	void SetupDynamicStates(const std::array<VkDynamicState, 2>& a_dynamicStates, VkPipelineDynamicStateCreateInfo& a_dynamicStateCreationInfo);
	void SetupDescriptorSetLayout(const VkDescriptorSetLayout& a_descriptorSetLayout, VkPipelineLayoutCreateInfo& a_pipelineLayoutInfo, VkDevice a_device);
	void PushPipelineInfo(VkGraphicsPipelineCreateInfo& a_pipelineCreateInfo, const std::span<VkPipelineShaderStageCreateInfo>& a_shaderStages, const VkPipelineVertexInputStateCreateInfo& a_vertexInputCreateInfo, const VkPipelineInputAssemblyStateCreateInfo& a_inputAssembly, const VkPipelineViewportStateCreateInfo& a_viewportStateCreateInfo, const VkPipelineRasterizationStateCreateInfo& a_rasterizerCreateInfo, const VkPipelineMultisampleStateCreateInfo& a_multisamplingCreateInfo, const VkPipelineDepthStencilStateCreateInfo& a_depthStencil, const VkPipelineColorBlendStateCreateInfo& a_colorBlending, const VkPipelineDynamicStateCreateInfo& a_dynamicStateCreationInfo, const VkRenderPass& a_renderPass, const VkDevice& a_device);

	VkPipeline m_graphicsPipeline { nullptr };
	VkPipelineLayout m_pipelineLayout { nullptr };
};
