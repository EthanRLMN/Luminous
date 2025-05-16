#include "ResourceManager/ResourceManager.hpp"

#include <ranges>

#include "IDevice.hpp"
#include "IMultiSampling.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"


ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager l_instance{};
    return l_instance;
}


void ResourceManager::Destroy(IDevice* a_device)
{
    for (IResource* const& l_resource : GetInstance().m_resources | std::views::values)
    {
        if (l_resource)
        {
            l_resource->Destroy(a_device);
            delete (l_resource);
        }
    }
    delete GetInstance().m_meshLoader;

    if (GetInstance().m_standardSampler != nullptr)
    {
        vkDestroySampler(a_device->CastVulkan()->GetDevice(), GetInstance().m_standardSampler, nullptr);
        GetInstance().m_standardSampler = nullptr;
    }

    if (GetInstance().m_rendererSampler != nullptr)
    {
        vkDestroySampler(a_device->CastVulkan()->GetDevice(), GetInstance().m_rendererSampler, nullptr);
        GetInstance().m_rendererSampler = nullptr;
    }
}

void ResourceManager::CreateRendererSampler(IDevice* a_device, SamplingCount a_msaaCount)
{
    VkPhysicalDeviceProperties l_properties{};
    vkGetPhysicalDeviceProperties(a_device->CastVulkan()->GetPhysicalDevice(), &l_properties);

    VkSamplerCreateInfo l_samplerInfo{ };

    l_samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    l_samplerInfo.magFilter = VK_FILTER_LINEAR;
    l_samplerInfo.minFilter = VK_FILTER_LINEAR;
    l_samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    l_samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    l_samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    l_samplerInfo.anisotropyEnable = VK_TRUE;
    l_samplerInfo.maxAnisotropy = l_properties.limits.maxSamplerAnisotropy;
    l_samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    l_samplerInfo.unnormalizedCoordinates = VK_FALSE;
    l_samplerInfo.compareEnable = VK_FALSE;
    l_samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    l_samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    l_samplerInfo.minLod = 0.0f;
    l_samplerInfo.maxLod = static_cast<float>(a_msaaCount);
    l_samplerInfo.mipLodBias = 0.0f;
    l_samplerInfo.pNext = nullptr;

    if (vkCreateSampler(a_device->CastVulkan()->GetDevice(), &l_samplerInfo, nullptr, &m_rendererSampler) != VK_SUCCESS)
        DEBUG_LOG_ERROR("Vulkan Texture : Failed to create Texture Sampler!\n");
}


void ResourceManager::CreateStandardSampler(IDevice* a_device)
{
    VkSamplerCreateInfo l_samplerInfo{};

    l_samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    l_samplerInfo.magFilter = VK_FILTER_LINEAR;
    l_samplerInfo.minFilter = VK_FILTER_LINEAR;
    l_samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    l_samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    l_samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    l_samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    l_samplerInfo.anisotropyEnable = VK_FALSE;
    l_samplerInfo.maxAnisotropy = 1.0f;
    l_samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    l_samplerInfo.unnormalizedCoordinates = VK_FALSE;
    l_samplerInfo.compareEnable = VK_FALSE;
    l_samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    l_samplerInfo.mipLodBias = 0.0f;
    l_samplerInfo.minLod = 0.0f;
    l_samplerInfo.maxLod = VK_LOD_CLAMP_NONE;
    l_samplerInfo.pNext = nullptr;

    vkCreateSampler(a_device->CastVulkan()->GetDevice(), &l_samplerInfo, nullptr, &m_standardSampler);
}