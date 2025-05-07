
#include "Rendering/Vulkan/VulkanShaderModule.hpp"

#include "Rendering/Vulkan/VulkanDevice.hpp"

#include "Utils/FileReaderUtils.hpp"

bool VulkanShaderModule::Create(IDevice* a_device, const std::string& a_path)
{
    const std::vector<char> l_code = ReadFile(a_path);

    VkShaderModuleCreateInfo l_createInfo{};
    l_createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    l_createInfo.codeSize = l_code.size();
    l_createInfo.pCode = reinterpret_cast<const uint32_t*>(l_code.data());

    if (vkCreateShaderModule(a_device->CastVulkan()->GetDevice(), &l_createInfo, nullptr, &m_shaderModule) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create shader module!");
    }

    return true;
}

void VulkanShaderModule::Destroy(IDevice* a_device)
{
    vkDestroyShaderModule(a_device->CastVulkan()->GetDevice(), m_shaderModule, nullptr);
}

VkPipelineShaderStageCreateInfo VulkanShaderModule::CreateStage(const VkShaderStageFlagBits a_shaderType) const
{
    VkPipelineShaderStageCreateInfo l_shaderStageCreateInfo{ };
    l_shaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    l_shaderStageCreateInfo.stage = a_shaderType;
    l_shaderStageCreateInfo.module = m_shaderModule;
    l_shaderStageCreateInfo.pName = "main";
    l_shaderStageCreateInfo.pNext = nullptr;

    return l_shaderStageCreateInfo;
}

void VulkanShaderModule::BindShader(VkVertexInputBindingDescription& a_bindingDescription, std::array<VkVertexInputAttributeDescription, 3>& a_attributeDescriptions, VkPipelineVertexInputStateCreateInfo& a_vertexInputCreateInfo)
{
    a_bindingDescription.binding = 0;
    a_bindingDescription.stride = sizeof(Vertex);
    a_bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    // Position Attributes
    a_attributeDescriptions[0].binding = 0; // which binding the data is at (should be same above)
    a_attributeDescriptions[0].location = 0; // location in shader where data will be reset
    a_attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT; // format the date will take (also helps define size of data
    a_attributeDescriptions[0].offset = offsetof(Vertex, pos); // attribute is defined in the data for single vertex

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
