
#include "Rendering/Vulkan/VulkanShaderModule.hpp"

#include "Rendering/Vulkan/VulkanDevice.hpp"

bool VulkanShaderModule::Create(IDevice* a_device, const std::vector<char>& a_shaders)
{
    VkShaderModuleCreateInfo l_createInfo{};
    l_createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    l_createInfo.codeSize = a_shaders.size();
    l_createInfo.pCode = reinterpret_cast<const uint32_t*>(a_shaders.data());


    if (vkCreateShaderModule(a_device->CastVulkan()->GetDevice(), &l_createInfo, nullptr, &m_shaderModule) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create shader module!");
    }

    return false;
}
