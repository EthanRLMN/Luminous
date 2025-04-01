#include <array>

#include "Logger.hpp"
#include "Struct/VulkanUtilities.hpp"

#include "Utils/FileReaderUtils.hpp"

#include "Rendering/Vulkan/VulkanPipeline.hpp"
#include "Rendering/Vulkan/VulkanDescriptorSetLayout.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"


void VulkanPipeline::Create(IDevice* a_device, IRenderPass* a_renderPass, IDescriptorSetLayout* a_descriptionSetLayout)
{
	// TODO Split shader module creation and file reading
	std::vector<char> l_vertexShaderCode = ReadFile("Engine/Assets/Shaders/vert.spv");
	std::vector<char> l_fragmentShaderCode = ReadFile("Engine/Assets/Shaders/frag.spv");

	VkShaderModule vertexShaderModule = CreateShaderModule(a_device->CastVulkan()->GetDevice(), l_vertexShaderCode);
	VkShaderModule fragmentShaderModule = CreateShaderModule(a_device->CastVulkan()->GetDevice(), l_fragmentShaderCode);

	//vertex stage creation
	VkPipelineShaderStageCreateInfo l_vertexShaderCreateInfo { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO };
	VertexStageCreation(l_vertexShaderCreateInfo, vertexShaderModule);

	//fragment stage creation
	VkPipelineShaderStageCreateInfo l_fragmentShaderCreateInfo { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO };
	FragmentStageCreation(l_fragmentShaderCreateInfo, fragmentShaderModule);

	//graphics pipeline creation info requires array  of shader
	VkPipelineShaderStageCreateInfo l_shaderStages[] = { l_vertexShaderCreateInfo, l_fragmentShaderCreateInfo };

	VkVertexInputBindingDescription l_bindingDescription { };
	std::array<VkVertexInputAttributeDescription, 3> l_attributeDescriptions { };
	VkPipelineVertexInputStateCreateInfo l_vertexInputCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };
	BindShaderAttributes(l_bindingDescription, l_attributeDescriptions, l_vertexInputCreateInfo);

	//Input Assembly
	VkPipelineInputAssemblyStateCreateInfo l_inputAssembly = { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
	SetupInputAssemblyState(l_inputAssembly);

	VkPipelineViewportStateCreateInfo l_viewportStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
	SetupViewportState(l_viewportStateCreateInfo);

	//rasterizer
	VkPipelineRasterizationStateCreateInfo l_rasterizerCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
	SetupRasterizerCreationInfo(l_rasterizerCreateInfo);

	//Multisampling
	VkPipelineMultisampleStateCreateInfo l_multisamplingCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
	SetupMultisamplingState(l_multisamplingCreateInfo);

	VkPipelineDepthStencilStateCreateInfo l_depthStencil { VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
	SetupDepthStencilState(l_depthStencil);

	VkPipelineColorBlendAttachmentState l_colorBlendAttachment { };
	SetupColorBlendAttachmentState(l_colorBlendAttachment);

	VkPipelineColorBlendStateCreateInfo l_colorBlending { VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
	SetupColorBlendingState(l_colorBlending, l_colorBlendAttachment);

	//dynamic states
	std::array<VkDynamicState, 2> l_dynamicStates { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
	VkPipelineDynamicStateCreateInfo l_dynamicStateCreationInfo { VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
	SetupDynamicStates(l_dynamicStates, l_dynamicStateCreationInfo);

	VkPipelineLayoutCreateInfo l_pipelineLayoutInfo { VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
	l_pipelineLayoutInfo.setLayoutCount = 1;

	VkDescriptorSetLayout l_descriptorSetLayout = a_descriptionSetLayout->CastVulkan()->GetDescriptorSetLayout(); //create descriptorSetLayout has a local variable
	SetupDescriptorSetLayout(l_descriptorSetLayout, l_pipelineLayoutInfo, a_device->CastVulkan()->GetDevice());

	//Graphic pipeline creation
	VkGraphicsPipelineCreateInfo l_pipelineCreateInfo { VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };
	PushPipelineInfo(l_pipelineCreateInfo, l_shaderStages, l_vertexInputCreateInfo, l_inputAssembly, l_viewportStateCreateInfo, l_rasterizerCreateInfo, l_multisamplingCreateInfo, l_depthStencil, l_colorBlending, l_dynamicStateCreationInfo, a_renderPass->CastVulkan()->GetRenderPass(), a_device->CastVulkan()->GetDevice());

	//destroy shader module no longer needed after pipeline created
	vkDestroyShaderModule(a_device->CastVulkan()->GetDevice(), fragmentShaderModule, nullptr);
	vkDestroyShaderModule(a_device->CastVulkan()->GetDevice(), vertexShaderModule, nullptr);
	DEBUG_LOG_INFO("Vulkan Graphic Pipeline : Pipeline Created!\n");
}


void VulkanPipeline::Destroy(IDevice* a_device)
{
	vkDestroyPipeline(a_device->CastVulkan()->GetDevice(), m_graphicsPipeline, nullptr);
	vkDestroyPipelineLayout(a_device->CastVulkan()->GetDevice(), m_pipelineLayout, nullptr);
	DEBUG_LOG_INFO("Vulkan Graphic Pipeline : Pipeline destroyed!\n");
}


VkShaderModule VulkanPipeline::CreateShaderModule(const VkDevice a_device, const std::vector<char>& a_code)
{
	VkShaderModuleCreateInfo l_shaderModuleCreateInfo { VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
	l_shaderModuleCreateInfo.codeSize = a_code.size();
	l_shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(a_code.data());

	VkShaderModule l_shaderModule { };
	const VkResult l_result = vkCreateShaderModule(a_device, &l_shaderModuleCreateInfo, nullptr, &l_shaderModule);
	if (l_result != VK_SUCCESS)
		DEBUG_LOG_ERROR("Vulkan Pipeline : Shader Module creating failed!\n");

	return l_shaderModule;
}


void VulkanPipeline::VertexStageCreation(VkPipelineShaderStageCreateInfo& a_vertexShaderCreateInfo, const VkShaderModule& a_vertexShaderModule)
{
	a_vertexShaderCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	a_vertexShaderCreateInfo.module = a_vertexShaderModule;
	a_vertexShaderCreateInfo.pName = "main";
}


void VulkanPipeline::FragmentStageCreation(VkPipelineShaderStageCreateInfo& a_fragmentShaderCreateInfo, const VkShaderModule& a_fragmentShaderModule)
{
	a_fragmentShaderCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	a_fragmentShaderCreateInfo.module = a_fragmentShaderModule;
	a_fragmentShaderCreateInfo.pName = "main";
}


void VulkanPipeline::BindShaderAttributes(VkVertexInputBindingDescription& a_bindingDescription, std::array<VkVertexInputAttributeDescription, 3> a_attributeDescriptions, VkPipelineVertexInputStateCreateInfo& a_vertexInputCreateInfo)
{
	a_bindingDescription.binding = 0;
	a_bindingDescription.stride = sizeof(Vertex);
	a_bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	//Position Attributes
	a_attributeDescriptions[0].binding = 0; //which binding the data is at (should be same above)
	a_attributeDescriptions[0].location = 0; //location in shader where data will be reset
	a_attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT; // format the date will take (also helps define size of data
	a_attributeDescriptions[0].offset = offsetof(Vertex, pos); // attribute is defined in the data for single vertex

	//Colour attribute
	a_attributeDescriptions[1].binding = 0;
	a_attributeDescriptions[1].location = 1;
	a_attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	a_attributeDescriptions[1].offset = offsetof(Vertex, color);

	//Tex Attribute
	a_attributeDescriptions[2].binding = 0;
	a_attributeDescriptions[2].location = 2;
	a_attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
	a_attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

	//--vertex Input
	a_vertexInputCreateInfo.vertexBindingDescriptionCount = 1;
	a_vertexInputCreateInfo.pVertexBindingDescriptions = &a_bindingDescription;
	a_vertexInputCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(a_attributeDescriptions.size());
	a_vertexInputCreateInfo.pVertexAttributeDescriptions = a_attributeDescriptions.data();
}


void VulkanPipeline::SetupInputAssemblyState(VkPipelineInputAssemblyStateCreateInfo& a_inputAssembly)
{
	a_inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	a_inputAssembly.primitiveRestartEnable = VK_FALSE;
}


void VulkanPipeline::SetupViewportState(VkPipelineViewportStateCreateInfo& a_viewportCreateInfo)
{
	a_viewportCreateInfo.viewportCount = 1;
	a_viewportCreateInfo.scissorCount = 1;
}


void VulkanPipeline::SetupRasterizerCreationInfo(VkPipelineRasterizationStateCreateInfo& a_rasterizerCreateInfo)
{
	a_rasterizerCreateInfo.depthClampEnable = VK_FALSE;
	a_rasterizerCreateInfo.rasterizerDiscardEnable = VK_FALSE;
	a_rasterizerCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
	a_rasterizerCreateInfo.lineWidth = 1.0f;
	a_rasterizerCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
	a_rasterizerCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
	a_rasterizerCreateInfo.depthBiasEnable = VK_FALSE;
}


void VulkanPipeline::SetupMultisamplingState(VkPipelineMultisampleStateCreateInfo& a_multisamplingCreateInfo)
{
	a_multisamplingCreateInfo.sampleShadingEnable = VK_FALSE;
	a_multisamplingCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
}


void VulkanPipeline::SetupDepthStencilState(VkPipelineDepthStencilStateCreateInfo& a_depthStencilCreateInfo)
{
	a_depthStencilCreateInfo.depthTestEnable = VK_TRUE;
	a_depthStencilCreateInfo.depthWriteEnable = VK_TRUE;
	a_depthStencilCreateInfo.depthCompareOp = VK_COMPARE_OP_LESS;
	a_depthStencilCreateInfo.depthBoundsTestEnable = VK_FALSE;
	a_depthStencilCreateInfo.stencilTestEnable = VK_FALSE;
}


void VulkanPipeline::SetupColorBlendAttachmentState(VkPipelineColorBlendAttachmentState& a_colorBlendAttachment)
{
	a_colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	a_colorBlendAttachment.blendEnable = VK_FALSE;
}


void VulkanPipeline::SetupColorBlendingState(VkPipelineColorBlendStateCreateInfo& a_colorBlendingCreateInfo, const VkPipelineColorBlendAttachmentState& a_colorBlendAttachment)
{
	a_colorBlendingCreateInfo.logicOpEnable = VK_FALSE;
	a_colorBlendingCreateInfo.logicOp = VK_LOGIC_OP_COPY;
	a_colorBlendingCreateInfo.attachmentCount = 1;
	a_colorBlendingCreateInfo.pAttachments = &a_colorBlendAttachment;
	a_colorBlendingCreateInfo.blendConstants[0] = 0.0f;
	a_colorBlendingCreateInfo.blendConstants[1] = 0.0f;
	a_colorBlendingCreateInfo.blendConstants[2] = 0.0f;
	a_colorBlendingCreateInfo.blendConstants[3] = 0.0f;
}


void VulkanPipeline::SetupDynamicStates(const std::array<VkDynamicState, 2>& a_dynamicStates, VkPipelineDynamicStateCreateInfo& a_dynamicStateCreationInfo)
{
	a_dynamicStateCreationInfo.dynamicStateCount = static_cast<uint32_t>(a_dynamicStates.size());
	a_dynamicStateCreationInfo.pDynamicStates = a_dynamicStates.data();
}


void VulkanPipeline::SetupDescriptorSetLayout(const VkDescriptorSetLayout& a_descriptorSetLayout, VkPipelineLayoutCreateInfo& a_pipelineLayoutInfo, const VkDevice a_device)
{
	a_pipelineLayoutInfo.pSetLayouts = &a_descriptorSetLayout;

	//Create pipeline layout
	const VkResult l_result = vkCreatePipelineLayout(a_device, &a_pipelineLayoutInfo, nullptr, &m_pipelineLayout);
	if (l_result != VK_SUCCESS)
		throw std::runtime_error("Failed to create Pipeline layout");
}


void VulkanPipeline::PushPipelineInfo(VkGraphicsPipelineCreateInfo& a_pipelineCreateInfo, const std::span<VkPipelineShaderStageCreateInfo>& a_shaderStages, const VkPipelineVertexInputStateCreateInfo& a_vertexInputCreateInfo, const VkPipelineInputAssemblyStateCreateInfo& a_inputAssembly, const VkPipelineViewportStateCreateInfo& a_viewportStateCreateInfo, const VkPipelineRasterizationStateCreateInfo& a_rasterizerCreateInfo, const VkPipelineMultisampleStateCreateInfo& a_multisamplingCreateInfo, const VkPipelineDepthStencilStateCreateInfo& a_depthStencil, const VkPipelineColorBlendStateCreateInfo& a_colorBlending, const VkPipelineDynamicStateCreateInfo& a_dynamicStateCreationInfo, const VkRenderPass& a_renderPass, const VkDevice& a_device)
{
	a_pipelineCreateInfo.stageCount = 2;
	a_pipelineCreateInfo.pStages = a_shaderStages.data();
	a_pipelineCreateInfo.pVertexInputState = &a_vertexInputCreateInfo;
	a_pipelineCreateInfo.pInputAssemblyState = &a_inputAssembly;
	a_pipelineCreateInfo.pViewportState = &a_viewportStateCreateInfo;
	a_pipelineCreateInfo.pRasterizationState = &a_rasterizerCreateInfo;
	a_pipelineCreateInfo.pMultisampleState = &a_multisamplingCreateInfo;
	a_pipelineCreateInfo.pDepthStencilState = &a_depthStencil;
	a_pipelineCreateInfo.pColorBlendState = &a_colorBlending;
	a_pipelineCreateInfo.pDynamicState = &a_dynamicStateCreationInfo;
	a_pipelineCreateInfo.layout = m_pipelineLayout;
	a_pipelineCreateInfo.renderPass = a_renderPass;
	a_pipelineCreateInfo.subpass = 0;
	a_pipelineCreateInfo.basePipelineHandle = nullptr;
	a_pipelineCreateInfo.basePipelineIndex = -1;

	const VkResult l_result = vkCreateGraphicsPipelines(a_device, nullptr, 1, &a_pipelineCreateInfo, nullptr, &m_graphicsPipeline);
	if (l_result != VK_SUCCESS)
		DEBUG_LOG_ERROR("Failed to create a Graphics Pipeline!\n");
}
