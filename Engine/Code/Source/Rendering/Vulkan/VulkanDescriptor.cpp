#include "ITexture.hpp"

#include "IDevice.hpp"

#include "Rendering/Vulkan/VulkanDescriptor.hpp"

#include "IDescriptorSetLayout.hpp"
#include "Rendering/Vulkan/VulkanBuffer.hpp"
#include "Rendering/Vulkan/VulkanDescriptorSetLayout.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanTexture.hpp"

#include "EntitySystem/Components/LightComponent.hpp"
#include "Struct/VulkanUtilities.hpp"


void VulkanDescriptor::Create(IDevice* a_device, IDescriptorSetLayout* a_descriptorSetLayout, ITexture* a_texture, IBuffer* a_buffer)
{
    SetBuffers(a_buffer);
    CreateDescriptorPool(a_device);
    CreateImGUIDescriptorPool(a_device);
    CreateDescriptorSets(a_device, a_descriptorSetLayout, a_texture);
    DEBUG_LOG_INFO("Vulkan Descriptors : Descriptors created!\n");
}


void VulkanDescriptor::SetBuffers(IBuffer* a_buffer)
{
    m_uniformBuffer = a_buffer->CastVulkan()->GetUniformBuffer();
    m_uniformBuffersMemory = a_buffer->CastVulkan()->GetUniformBuffersMemory();
    m_uniformBuffersMapped = a_buffer->CastVulkan()->GetUniformBuffersMapped();

    m_lightUniformBuffer = a_buffer->CastVulkan()->GetLightUniformBuffer();
    m_lightUniformBuffersMemory = a_buffer->CastVulkan()->GetLightUniformBuffersMemory();
    m_lightUniformBuffersMapped = a_buffer->CastVulkan()->GetLightUniformBuffersMapped();
}


void VulkanDescriptor::Destroy(IDevice* a_device)
{
    vkDeviceWaitIdle(a_device->CastVulkan()->GetDevice());
    vkDestroyDescriptorPool(a_device->CastVulkan()->GetDevice(), m_descriptorPool, nullptr);
    vkDestroyDescriptorPool(a_device->CastVulkan()->GetDevice(), m_imguiDescriptorPool, nullptr);
    DEBUG_LOG_INFO("Vulkan Descriptors : Descriptor Pools Destroyed!\n");
}


void VulkanDescriptor::CreateDescriptorPool(IDevice* a_device)
{
    std::array<VkDescriptorPoolSize, 3> l_poolSizes{};
    l_poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    l_poolSizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
    l_poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    l_poolSizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
    l_poolSizes[2].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    l_poolSizes[2].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

    VkDescriptorPoolCreateInfo l_poolInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
    l_poolInfo.poolSizeCount = static_cast<uint32_t>(l_poolSizes.size());
    l_poolInfo.pPoolSizes = l_poolSizes.data();
    l_poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
    l_poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;

    if (vkCreateDescriptorPool(a_device->CastVulkan()->GetDevice(), &l_poolInfo, nullptr, &m_descriptorPool) != VK_SUCCESS)
        DEBUG_LOG_ERROR("Failed to create descriptor pool\n");

    DEBUG_LOG_INFO("Vulkan Descriptors : DescriptorPool created!\n");

    /*// LIGHT EDIT 99
    VkDescriptorPoolSize l_lightPoolSize{};
    l_lightPoolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    l_lightPoolSize.descriptorCount = 1;

    VkDescriptorPoolCreateInfo l_lightPoolInfo{};
    l_lightPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    l_lightPoolInfo.poolSizeCount = 1;
    l_lightPoolInfo.pPoolSizes = &l_lightPoolSize;
    l_lightPoolInfo.maxSets = 1;

    vkCreateDescriptorPool(a_device->CastVulkan()->GetDevice(), &l_lightPoolInfo, nullptr, &m_lightDescriptorPool);*/
}

void VulkanDescriptor::CreateImGUIDescriptorPool(IDevice* a_device)
{
    constexpr std::array<VkDescriptorPoolSize, 11> l_poolSizes = {
        VkDescriptorPoolSize{ VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
        VkDescriptorPoolSize{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
        VkDescriptorPoolSize{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
        VkDescriptorPoolSize{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
        VkDescriptorPoolSize{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
        VkDescriptorPoolSize{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
        VkDescriptorPoolSize{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
        VkDescriptorPoolSize{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
        VkDescriptorPoolSize{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
        VkDescriptorPoolSize{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
        VkDescriptorPoolSize{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
    };

    VkDescriptorPoolCreateInfo poolInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
    poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    poolInfo.maxSets = 1000;
    poolInfo.poolSizeCount = static_cast<uint32_t>(l_poolSizes.size());
    poolInfo.pPoolSizes = l_poolSizes.data();

    if (vkCreateDescriptorPool(a_device->CastVulkan()->GetDevice(), &poolInfo, nullptr, &m_imguiDescriptorPool) != VK_SUCCESS)
        DEBUG_LOG_ERROR("Failed to create ImGui descriptor pool");

    DEBUG_LOG_INFO("ImGui DescriptorPool created!");
}


void VulkanDescriptor::CreateDescriptorSets(IDevice* a_device, IDescriptorSetLayout* a_descriptorSetLayout, ITexture* a_texture)
{
    const std::vector<VkDescriptorSetLayout> l_layouts(MAX_FRAMES_IN_FLIGHT, a_descriptorSetLayout->CastVulkan()->GetDescriptorSetLayout());

    VkDescriptorSetAllocateInfo l_allocateInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO };
    l_allocateInfo.descriptorPool = m_descriptorPool;
    l_allocateInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
    l_allocateInfo.pSetLayouts = l_layouts.data();

    m_descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
    if (vkAllocateDescriptorSets(a_device->CastVulkan()->GetDevice(), &l_allocateInfo, m_descriptorSets.data()) != VK_SUCCESS)
        DEBUG_LOG_ERROR("failed to allocate descriptor sets !\n");


    /*
    std::vector<VkDescriptorSetLayout> l_lightLayout = { a_descriptorSetLayout->CastVulkan()->GetLightDescriptorSetLayout() };
    VkDescriptorSetAllocateInfo l_lightAllocInfo{};
    l_lightAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    l_lightAllocInfo.descriptorPool = m_lightDescriptorPool;
    l_lightAllocInfo.descriptorSetCount = 1;
    l_lightAllocInfo.pSetLayouts = l_lightLayout.data();

    vkAllocateDescriptorSets(a_device->CastVulkan()->GetDevice(), &l_lightAllocInfo, &m_lightDescriptorSets);*/


    UpdateDescriptorSets(a_device, a_texture);
}


void VulkanDescriptor::UpdateDescriptorSets(IDevice* a_device, ITexture* a_texture) const
{
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
    {
        VkDescriptorBufferInfo l_bufferInfo{};
        l_bufferInfo.buffer = m_uniformBuffer[i];
        l_bufferInfo.offset = 0;
        l_bufferInfo.range = sizeof(UniformBufferObject);

        VkDescriptorImageInfo l_imageInfo{};
        l_imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        l_imageInfo.imageView = a_texture->CastVulkan()->GetTextureImageView();
        l_imageInfo.sampler = a_texture->CastVulkan()->GetTextureSampler();

        
        VkDescriptorBufferInfo l_lightBufferInfo{};
        l_lightBufferInfo.buffer = m_lightUniformBuffer[i];
        l_lightBufferInfo.offset = 0;
        l_lightBufferInfo.range = VK_WHOLE_SIZE;

        std::array<VkWriteDescriptorSet, 3> l_descriptorWrites{ VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET };
        l_descriptorWrites[0].dstSet = m_descriptorSets[i];
        l_descriptorWrites[0].dstBinding = 0;
        l_descriptorWrites[0].dstArrayElement = 0;
        l_descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        l_descriptorWrites[0].descriptorCount = 1;
        l_descriptorWrites[0].pBufferInfo = &l_bufferInfo;

        l_descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        l_descriptorWrites[1].dstSet = m_descriptorSets[i];
        l_descriptorWrites[1].dstBinding = 1;
        l_descriptorWrites[1].dstArrayElement = 0;
        l_descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        l_descriptorWrites[1].descriptorCount = 1;
        l_descriptorWrites[1].pImageInfo = &l_imageInfo;

        
        l_descriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        l_descriptorWrites[2].dstSet = m_descriptorSets[i];
        l_descriptorWrites[2].dstBinding = 2;
        l_descriptorWrites[2].dstArrayElement = 0;
        l_descriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        l_descriptorWrites[2].descriptorCount = 1;
        l_descriptorWrites[2].pBufferInfo = &l_lightBufferInfo;


        vkUpdateDescriptorSets(a_device->CastVulkan()->GetDevice(), static_cast<uint32_t>(l_descriptorWrites.size()), l_descriptorWrites.data(), 0, nullptr);
        DEBUG_LOG_INFO("Vulkan Descriptors : DescriptorSet created!\n");
    }

    /*// LIGHT EDIT 99
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = m_lightUniformBuffer;
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(LightComponent) * 32 + sizeof(int);

    VkWriteDescriptorSet descriptorWrite{};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = m_lightDescriptorSets;
    descriptorWrite.dstBinding = 0;
    descriptorWrite.dstArrayElement = 0;
    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrite.descriptorCount = 1;
    descriptorWrite.pBufferInfo = &bufferInfo;

    vkUpdateDescriptorSets(a_device->CastVulkan()->GetDevice(), 1, &descriptorWrite, 0, nullptr);*/


}
