
#include "Rendering/Vulkan/VulkanShaderModule.hpp"

#include "Rendering/Vulkan/VulkanDevice.hpp"

#include "Utils/FileReaderUtils.hpp"

bool VulkanShaderModule::Create(IDevice* a_device, const std::string& a_path)
{

    std::vector<char> l_code = ReadFile(a_path);

    VkShaderModuleCreateInfo l_createInfo{};
    l_createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    l_createInfo.codeSize = l_code.size();
    l_createInfo.pCode = reinterpret_cast<const uint32_t*>(l_code.data());


    if (vkCreateShaderModule(a_device->CastVulkan()->GetDevice(), &l_createInfo, nullptr, &m_shaderModule) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create shader module!");
    }

    return false;
}

void VulkanShaderModule::Destroy(IDevice* a_device)
{
    vkDestroyShaderModule(a_device->CastVulkan()->GetDevice(), m_shaderModule, nullptr);
}
