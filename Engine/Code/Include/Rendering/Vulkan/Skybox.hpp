#pragma once 
#include <array>

#include "Logger.hpp"
#include "Struct/VulkanUtilities.hpp"

#include "Utils/FileReaderUtils.hpp"

#include "Rendering/Vulkan/VulkanPipeline.hpp"
#include "Rendering/Vulkan/VulkanDescriptorSetLayout.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/Vulkan/VulkanShader.hpp"
#include "ResourceManager/Resource.hpp"
#include "ResourceManager/ResourceManager.hpp"


struct SkyboxUBO
{
    Maths::Matrix4 view;
    Maths::Matrix4 projection;
};

class Skybox
{
public:

    void CreateSkyBox(IDevice* a_device, IRenderPass* a_renderPass, IDescriptorSetLayout* a_descriptionSetLayout, VkPipelineLayout* a_pipeline_layout);

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
    void SetupDescriptorSetLayout(const std::vector<VkDescriptorSetLayout> a_descriptorSetLayouts, VkPipelineLayoutCreateInfo& a_pipelineLayoutInfo, const VkDevice a_device, VkPipelineLayout* a_pipeline_layout);

    VkPipeline m_skyboxPipeline{ nullptr };

private:


    std::vector<Maths::Vector3> skyboxVertices = {
        { -1.0f, 1.0f, -1.0f },
        { -1.0f, -1.0f, -1.0f },
        { 1.0f, -1.0f, -1.0f },
        { 1.0f, -1.0f, -1.0f },
        { 1.0f, 1.0f, -1.0f },
        { -1.0f, 1.0f, -1.0f },

        { -1.0f, -1.0f, 1.0f },
        { -1.0f, -1.0f, -1.0f },
        { -1.0f, 1.0f, -1.0f },
        { -1.0f, 1.0f, -1.0f },
        { -1.0f, 1.0f, 1.0f },
        { -1.0f, -1.0f, 1.0f },

        { 1.0f, -1.0f, -1.0f },
        { 1.0f, -1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, -1.0f },
        { 1.0f, -1.0f, -1.0f },

        { -1.0f, -1.0f, 1.0f },
        { -1.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f },
        { 1.0f, -1.0f, 1.0f },
        { -1.0f, -1.0f, 1.0f },

        { -1.0f, 1.0f, -1.0f },
        { 1.0f, 1.0f, -1.0f },
        { 1.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f },
        { -1.0f, 1.0f, 1.0f },
        { -1.0f, 1.0f, -1.0f },

        { -1.0f, -1.0f, -1.0f },
        { -1.0f, -1.0f, 1.0f },
        { 1.0f, -1.0f, -1.0f },
        { 1.0f, -1.0f, -1.0f },
        { -1.0f, -1.0f, 1.0f },
        { 1.0f, -1.0f, 1.0f }
    };
};


