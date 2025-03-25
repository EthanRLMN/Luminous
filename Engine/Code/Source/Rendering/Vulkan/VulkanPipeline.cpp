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
	std::vector<char> l_vertexShaderCode = ReadFile("Engine/Assets/Shaders/vert.spv");
	std::vector<char> l_fragmentShaderCode = ReadFile("Engine/Assets/Shaders/frag.spv");

	VkShaderModule vertexShaderModule = CreateShaderModule(a_device->CastVulkan()->GetDevice(), l_vertexShaderCode);
	VkShaderModule fragmentShaderModule = CreateShaderModule(a_device->CastVulkan()->GetDevice(), l_fragmentShaderCode);

	//vertex stage creation
	VkPipelineShaderStageCreateInfo l_vertexShaderCreateInfo{};
	l_vertexShaderCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	l_vertexShaderCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	l_vertexShaderCreateInfo.module = vertexShaderModule;
	l_vertexShaderCreateInfo.pName = "main";

	//fragment stage creation
	VkPipelineShaderStageCreateInfo l_fragmentShaderCreateInfo{};
	l_fragmentShaderCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	l_fragmentShaderCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	l_fragmentShaderCreateInfo.module = fragmentShaderModule;
	l_fragmentShaderCreateInfo.pName = "main";

	//graphics pipeline creation info requires array  of shader
	VkPipelineShaderStageCreateInfo l_shaderStages[] = { l_vertexShaderCreateInfo ,l_fragmentShaderCreateInfo };

	VkVertexInputBindingDescription l_bindingDescription{};
	l_bindingDescription.binding = 0;
	l_bindingDescription.stride = sizeof(Vertex);
	l_bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	std::array<VkVertexInputAttributeDescription, 3> l_attributeDescriptions{};
	//Position Attributes
	l_attributeDescriptions[0].binding = 0;   //which binding the data is at (should be same above)
	l_attributeDescriptions[0].location = 0;  //location in shader where data will be reset
	l_attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT; // format the date will take (also helps define size of data
	l_attributeDescriptions[0].offset = offsetof(Vertex, pos); // attribute is defined in the data for single vertex
	//Colour attribute
	l_attributeDescriptions[1].binding = 0;
	l_attributeDescriptions[1].location = 1;
	l_attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	l_attributeDescriptions[1].offset = offsetof(Vertex, color);
	//Tex Attribute
	l_attributeDescriptions[2].binding = 0;
	l_attributeDescriptions[2].location = 2;
	l_attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
	l_attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

	//--vertex Input
	VkPipelineVertexInputStateCreateInfo l_vertexInputCreateInfo = {};
	l_vertexInputCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	l_vertexInputCreateInfo.vertexBindingDescriptionCount = 1;
	l_vertexInputCreateInfo.pVertexBindingDescriptions = &l_bindingDescription;
	l_vertexInputCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(l_attributeDescriptions.size());
	l_vertexInputCreateInfo.pVertexAttributeDescriptions = l_attributeDescriptions.data();

	//Input Assembly
	VkPipelineInputAssemblyStateCreateInfo l_inputAssembly = {};
	l_inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	l_inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	l_inputAssembly.primitiveRestartEnable = VK_FALSE;

	VkPipelineViewportStateCreateInfo l_viewportStateCreateInfo = {};
	l_viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	l_viewportStateCreateInfo.viewportCount = 1;
	l_viewportStateCreateInfo.scissorCount = 1;

	//rasterizer
	VkPipelineRasterizationStateCreateInfo l_rasterizerCreateInfo = {};
	l_rasterizerCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	l_rasterizerCreateInfo.depthClampEnable = VK_FALSE;
	l_rasterizerCreateInfo.rasterizerDiscardEnable = VK_FALSE;
	l_rasterizerCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
	l_rasterizerCreateInfo.lineWidth = 1.0f;
	l_rasterizerCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
	l_rasterizerCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
	l_rasterizerCreateInfo.depthBiasEnable = VK_FALSE;

	//Multisampling
	VkPipelineMultisampleStateCreateInfo l_multisamplingCreateInfo = {};
	l_multisamplingCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	l_multisamplingCreateInfo.sampleShadingEnable = VK_FALSE;
	l_multisamplingCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	VkPipelineDepthStencilStateCreateInfo l_depthStencil{};
	l_depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	l_depthStencil.depthTestEnable = VK_TRUE;
	l_depthStencil.depthWriteEnable = VK_TRUE;
	l_depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
	l_depthStencil.depthBoundsTestEnable = VK_FALSE;
	l_depthStencil.stencilTestEnable = VK_FALSE;

	VkPipelineColorBlendAttachmentState l_colorBlendAttachment{};
	l_colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	l_colorBlendAttachment.blendEnable = VK_FALSE;

	VkPipelineColorBlendStateCreateInfo l_colorBlending{};
	l_colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	l_colorBlending.logicOpEnable = VK_FALSE;
	l_colorBlending.logicOp = VK_LOGIC_OP_COPY;
	l_colorBlending.attachmentCount = 1;
	l_colorBlending.pAttachments = &l_colorBlendAttachment;
	l_colorBlending.blendConstants[0] = 0.0f;
	l_colorBlending.blendConstants[1] = 0.0f;
	l_colorBlending.blendConstants[2] = 0.0f;
	l_colorBlending.blendConstants[3] = 0.0f;

	//dynamic states
	std::vector<VkDynamicState> l_dynamicStates{
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};

	//Dynamic state creation info
	VkPipelineDynamicStateCreateInfo l_dynamicStateCreationInfo{};
	l_dynamicStateCreationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	l_dynamicStateCreationInfo.dynamicStateCount = static_cast<uint32_t>(l_dynamicStates.size());
	l_dynamicStateCreationInfo.pDynamicStates = l_dynamicStates.data();

	VkPipelineLayoutCreateInfo l_pipelineLayoutInfo{};
	l_pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	l_pipelineLayoutInfo.setLayoutCount = 1;
	
    VkDescriptorSetLayout l_descriptorSetLayout = a_descriptionSetLayout->CastVulkan()->GetDescriptorSetLayout(); //create descriptorSetLayout has a local variable
    l_pipelineLayoutInfo.pSetLayouts = &l_descriptorSetLayout;

	//Create pipeline layout 
	VkResult l_result = vkCreatePipelineLayout(a_device->CastVulkan()->GetDevice(), &l_pipelineLayoutInfo, nullptr, &m_pipelineLayout);
	if (l_result != VK_SUCCESS)
		throw std::runtime_error("Failed to create Pipeline layout");

	//Graphic pipeline creation
	VkGraphicsPipelineCreateInfo l_pipelineCreateInfo{};
	l_pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	l_pipelineCreateInfo.stageCount = 2;
	l_pipelineCreateInfo.pStages = l_shaderStages;
	l_pipelineCreateInfo.pVertexInputState = &l_vertexInputCreateInfo;
	l_pipelineCreateInfo.pInputAssemblyState = &l_inputAssembly;
	l_pipelineCreateInfo.pViewportState = &l_viewportStateCreateInfo;
	l_pipelineCreateInfo.pRasterizationState = &l_rasterizerCreateInfo;
	l_pipelineCreateInfo.pMultisampleState = &l_multisamplingCreateInfo;
	l_pipelineCreateInfo.pDepthStencilState = &l_depthStencil;
	l_pipelineCreateInfo.pColorBlendState = &l_colorBlending;
	l_pipelineCreateInfo.pDynamicState = &l_dynamicStateCreationInfo;
	l_pipelineCreateInfo.layout = m_pipelineLayout;
	l_pipelineCreateInfo.renderPass = a_renderPass->CastVulkan()->GetRenderPass();
	l_pipelineCreateInfo.subpass = 0;
	l_pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
	l_pipelineCreateInfo.basePipelineIndex = -1;

	l_result = vkCreateGraphicsPipelines(a_device->CastVulkan()->GetDevice(), VK_NULL_HANDLE, 1, &l_pipelineCreateInfo, nullptr, &m_graphicsPipeline);
	if (l_result != VK_SUCCESS)
		throw std::runtime_error("Failed to create a Graphics Pipeline!");

	//destroy sahder module no longer needed after pipeline created
	vkDestroyShaderModule(a_device->CastVulkan()->GetDevice(), fragmentShaderModule, nullptr);
	vkDestroyShaderModule(a_device->CastVulkan()->GetDevice(), vertexShaderModule, nullptr);
}

void VulkanPipeline::Destroy()
{
	DEBUG_LOG_INFO("Vulkan Pipeline : Pipeline destroyed!\n");
}

VkShaderModule VulkanPipeline::CreateShaderModule(VkDevice a_device, const std::vector<char>& a_code)
{
	VkShaderModuleCreateInfo l_shaderModuleCreateInfo{};
	l_shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	l_shaderModuleCreateInfo.codeSize = a_code.size();
	l_shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(a_code.data());

	VkShaderModule l_shaderModule{};
	const VkResult l_result = vkCreateShaderModule(a_device, &l_shaderModuleCreateInfo, nullptr, &l_shaderModule);
	if (l_result != VK_SUCCESS)
		DEBUG_LOG_ERROR("Vulkan Pipeline : Shader Module creating failed!\n");

	return l_shaderModule;
}