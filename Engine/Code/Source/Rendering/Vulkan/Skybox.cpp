#include "Rendering/Vulkan/Skybox.hpp"


void Skybox::CreateSkyBox(IDevice* a_device, IRenderPass* a_renderPass, IDescriptorSetLayout* a_descriptionSetLayout, VkPipelineLayout* a_pipeline_layout)
{
    IResourceParams l_shaderParams{ a_device };
    l_shaderParams.m_vertexShaderPath = "Engine/Assets/Default/Shaders/skyboxfrag.spv";
    l_shaderParams.m_fragmentShaderPath = "Engine/Assets/Default/Shaders/skyboxfrag.spv";
    VulkanShader* l_shader = ResourceManager::GetInstance().LoadResource<VulkanShader>(l_shaderParams);

    // graphics pipeline creation info requires an array of shader
    std::array<VkPipelineShaderStageCreateInfo, 2> l_shaderStages = {
        l_shader->GetVertexShaderModule()->CreateStage(VK_SHADER_STAGE_VERTEX_BIT),
        l_shader->GetFragmentShaderModule()->CreateStage(VK_SHADER_STAGE_FRAGMENT_BIT)
    };

    VkVertexInputBindingDescription l_bindingDescription{};
    std::array<VkVertexInputAttributeDescription, 4> l_attributeDescriptions{};
    VkPipelineVertexInputStateCreateInfo l_vertexInputCreateInfo{};
    l_vertexInputCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    l_vertexInputCreateInfo.pNext = nullptr;
    l_shader->GetVertexShaderModule()->BindShader(l_bindingDescription, l_attributeDescriptions, l_vertexInputCreateInfo);

    // Input Assembly
    VkPipelineInputAssemblyStateCreateInfo l_inputAssembly{};
    l_inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    l_inputAssembly.pNext = nullptr;
    SetupInputAssemblyState(l_inputAssembly);

    VkPipelineViewportStateCreateInfo l_viewportStateCreateInfo{};
    l_viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    l_viewportStateCreateInfo.pNext = nullptr;
    SetupViewportState(l_viewportStateCreateInfo);

    // rasterizer
    VkPipelineRasterizationStateCreateInfo l_rasterizerCreateInfo{};
    l_rasterizerCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    l_rasterizerCreateInfo.pNext = nullptr;
    SetupRasterizerCreationInfo(l_rasterizerCreateInfo);

    // Multisampling
    VkPipelineMultisampleStateCreateInfo l_multisamplingCreateInfo{};
    l_multisamplingCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    l_multisamplingCreateInfo.pNext = nullptr;
    SetupSamplingState(l_multisamplingCreateInfo, a_device->CastVulkan()->GetMSAASamples());

    VkPipelineDepthStencilStateCreateInfo l_depthStencil{};
    l_depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    l_depthStencil.pNext = nullptr;
    SetupDepthStencilState(l_depthStencil);

    VkPipelineColorBlendAttachmentState l_colorBlendAttachment{};
    SetupColorBlendAttachmentState(l_colorBlendAttachment);

    VkPipelineColorBlendStateCreateInfo l_colorBlending{};
    l_colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    l_colorBlending.pNext = nullptr;
    SetupColorBlendingState(l_colorBlending, l_colorBlendAttachment);

    // dynamic states
    std::array<VkDynamicState, 2> l_dynamicStates{ VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
    VkPipelineDynamicStateCreateInfo l_dynamicStateCreationInfo{};
    SetupDynamicStates(l_dynamicStates, l_dynamicStateCreationInfo);

    VkPipelineLayoutCreateInfo l_pipelineLayoutInfo{};
    l_pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    l_pipelineLayoutInfo.setLayoutCount = 1;
    l_pipelineLayoutInfo.pNext = nullptr;

    VkPushConstantRange l_pushConstant;
    SetupPushConstants(l_pipelineLayoutInfo, l_pushConstant);


    VkDescriptorSetLayout l_descriptorSetLayout = a_descriptionSetLayout->CastVulkan()->GetDescriptorSetLayout();
    VkDescriptorSetLayout l_lightDescriptorSetLayout = a_descriptionSetLayout->CastVulkan()->GetTextureDescriptorSetLayout(); // create descriptorSetLayout has a local variable
    std::vector<VkDescriptorSetLayout> l_descriptorSetLayouts = { l_descriptorSetLayout, l_lightDescriptorSetLayout };
    SetupDescriptorSetLayout(l_descriptorSetLayouts, l_pipelineLayoutInfo, a_device->CastVulkan()->GetDevice(),a_pipeline_layout);


    DEBUG_LOG_INFO("Vulkan Skybox Pipeline : Pipeline Created!\n");
}


void Skybox::VertexStageCreation(VkPipelineShaderStageCreateInfo& a_vertexShaderCreateInfo, const VkShaderModule& a_vertexShaderModule)
{
    a_vertexShaderCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    a_vertexShaderCreateInfo.module = a_vertexShaderModule;
    a_vertexShaderCreateInfo.pName = "main";
}


void Skybox::FragmentStageCreation(VkPipelineShaderStageCreateInfo& a_fragmentShaderCreateInfo, const VkShaderModule& a_fragmentShaderModule)
{
    a_fragmentShaderCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    a_fragmentShaderCreateInfo.module = a_fragmentShaderModule;
    a_fragmentShaderCreateInfo.pName = "main";
}


void Skybox::BindShaderAttributes(VkVertexInputBindingDescription& a_bindingDescription, std::array<VkVertexInputAttributeDescription, 3> a_attributeDescriptions, VkPipelineVertexInputStateCreateInfo& a_vertexInputCreateInfo)
{
    a_bindingDescription.binding = 0;
    a_bindingDescription.stride = sizeof(Vertex);
    a_bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    // Position Attributes
    a_attributeDescriptions[0].binding = 0; // which binding the data is at (should be the same as above)
    a_attributeDescriptions[0].location = 0; // location in shader where data will be reset
    a_attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT; // format the date will take (also helps define the size of data
    a_attributeDescriptions[0].offset = offsetof(Vertex, pos); // attribute is defined in the data for a single vertex

    // Colour attribute
    a_attributeDescriptions[1].binding = 0;
    a_attributeDescriptions[1].location = 1;
    a_attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    a_attributeDescriptions[1].offset = offsetof(Vertex, color);

    // Tex Attribute
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


void Skybox::SetupInputAssemblyState(VkPipelineInputAssemblyStateCreateInfo& a_inputAssembly)
{
    a_inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    a_inputAssembly.primitiveRestartEnable = VK_FALSE;
}


void Skybox::SetupViewportState(VkPipelineViewportStateCreateInfo& a_viewportCreateInfo)
{
    a_viewportCreateInfo.viewportCount = 1;
    a_viewportCreateInfo.scissorCount = 1;
}


void Skybox::SetupRasterizerCreationInfo(VkPipelineRasterizationStateCreateInfo& a_rasterizerCreateInfo)
{
    a_rasterizerCreateInfo.depthClampEnable = VK_FALSE;
    a_rasterizerCreateInfo.rasterizerDiscardEnable = VK_FALSE;
    a_rasterizerCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    a_rasterizerCreateInfo.lineWidth = 1.0f;
    a_rasterizerCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    a_rasterizerCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    a_rasterizerCreateInfo.depthBiasEnable = VK_FALSE;
}


void Skybox::SetupSamplingState(VkPipelineMultisampleStateCreateInfo& a_multisamplingCreateInfo, const VkSampleCountFlagBits a_sampleCount)
{
    a_multisamplingCreateInfo.sampleShadingEnable = VK_TRUE;
    a_multisamplingCreateInfo.rasterizationSamples = a_sampleCount;
    a_multisamplingCreateInfo.minSampleShading = 0.2f;
}


void Skybox::SetupDepthStencilState(VkPipelineDepthStencilStateCreateInfo& a_depthStencilCreateInfo)
{
    a_depthStencilCreateInfo.depthTestEnable = VK_TRUE;
    a_depthStencilCreateInfo.depthWriteEnable = VK_TRUE;
    a_depthStencilCreateInfo.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    a_depthStencilCreateInfo.depthBoundsTestEnable = VK_FALSE;
    a_depthStencilCreateInfo.stencilTestEnable = VK_FALSE;
}


void Skybox::SetupColorBlendAttachmentState(VkPipelineColorBlendAttachmentState& a_colorBlendAttachment)
{
    a_colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    a_colorBlendAttachment.blendEnable = VK_FALSE;
}


void Skybox::SetupColorBlendingState(VkPipelineColorBlendStateCreateInfo& a_colorBlendingCreateInfo, const VkPipelineColorBlendAttachmentState& a_colorBlendAttachment)
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


void Skybox::SetupDynamicStates(const std::array<VkDynamicState, 2>& a_dynamicStates, VkPipelineDynamicStateCreateInfo& a_dynamicStateCreationInfo)
{
    a_dynamicStateCreationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    a_dynamicStateCreationInfo.dynamicStateCount = static_cast<uint32_t>(a_dynamicStates.size());
    a_dynamicStateCreationInfo.pDynamicStates = a_dynamicStates.data();
    a_dynamicStateCreationInfo.pNext = nullptr;
}

void Skybox::SetupPushConstants(VkPipelineLayoutCreateInfo& a_layout, VkPushConstantRange& a_pushConstant)
{
    a_pushConstant.offset = 0;
    a_pushConstant.size = sizeof(UniformBufferObject);
    a_pushConstant.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    a_layout.pPushConstantRanges = &a_pushConstant;
    a_layout.pushConstantRangeCount = 1;
}


void Skybox::SetupDescriptorSetLayout(const std::vector<VkDescriptorSetLayout> a_descriptorSetLayouts, VkPipelineLayoutCreateInfo& a_pipelineLayoutInfo, const VkDevice a_device,VkPipelineLayout* a_pipeline_layout)
{
    a_pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(a_descriptorSetLayouts.size());
    a_pipelineLayoutInfo.pSetLayouts = a_descriptorSetLayouts.data();

    // Create pipeline layout
    const VkResult l_result = vkCreatePipelineLayout(a_device, &a_pipelineLayoutInfo, nullptr, a_pipeline_layout);
    LOG_ASSERT_ERROR(l_result == VK_SUCCESS, "Vulkan Pipeline: Failed to create Pipeline layout!\n");
}
