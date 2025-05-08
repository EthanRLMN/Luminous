#include <array>

#include "Rendering/Vulkan/VulkanDescriptorSetLayout.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"


void VulkanDescriptorSetLayout::Create(IDevice* a_device)
{
	VkDescriptorSetLayoutBinding l_uboLayoutBinding = {};
	l_uboLayoutBinding.binding = 0;
	l_uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	l_uboLayoutBinding.descriptorCount = 1;
	l_uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	l_uboLayoutBinding.pImmutableSamplers = nullptr;

	VkDescriptorSetLayoutBinding l_samplerLayoutBinding = {};
	l_samplerLayoutBinding.binding = 1;
	l_samplerLayoutBinding.descriptorCount = 1;
	l_samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	l_samplerLayoutBinding.pImmutableSamplers = nullptr;
	l_samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

	const std::array<VkDescriptorSetLayoutBinding, 2> l_bindings = {l_uboLayoutBinding, l_samplerLayoutBinding};
	VkDescriptorSetLayoutCreateInfo l_layoutInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
	l_layoutInfo.bindingCount = static_cast<uint32_t>(l_bindings.size());
	l_layoutInfo.pBindings = l_bindings.data();

	const VkResult l_result = vkCreateDescriptorSetLayout(a_device->CastVulkan()->GetDevice(), &l_layoutInfo, nullptr, &m_descriptorSetLayout);
	if (l_result != VK_SUCCESS)
		DEBUG_LOG_ERROR("Vulkan Descriptor : Failed to create a descriptor set layout!\n");

	DEBUG_LOG_INFO("Vulkan DescriptorSetLayout : DescriptorSetLayout Created!\n");

	CreateTextureDescriptorLayout(a_device);
}

void VulkanDescriptorSetLayout::CreateTextureDescriptorLayout(IDevice* a_device)
{

    VkDescriptorSetLayoutBinding l_textureLayoutBinding = {};
    l_textureLayoutBinding.binding = 0;
    l_textureLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    l_textureLayoutBinding.descriptorCount = 1;
    l_textureLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    l_textureLayoutBinding.pImmutableSamplers = nullptr;


    const std::array<VkDescriptorSetLayoutBinding, 1> l_bindings = { l_textureLayoutBinding };
    VkDescriptorSetLayoutCreateInfo l_layoutInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
    l_layoutInfo.bindingCount = static_cast<uint32_t>(l_bindings.size());
    l_layoutInfo.pBindings = l_bindings.data();

    const VkResult l_result = vkCreateDescriptorSetLayout(a_device->CastVulkan()->GetDevice(), &l_layoutInfo, nullptr, &m_textureDescriptorSetLayout);
    if (l_result != VK_SUCCESS)
        DEBUG_LOG_ERROR("Vulkan Descriptor : Failed to create a texture descriptor set layout!\n");

    DEBUG_LOG_INFO("Vulkan DescriptorSetLayout : Texture's DescriptorSetLayout Created!\n");
}

void VulkanDescriptorSetLayout::Destroy(IDevice* a_device)
{
	vkDestroyDescriptorSetLayout(a_device->CastVulkan()->GetDevice(), m_descriptorSetLayout, nullptr);
    vkDestroyDescriptorSetLayout(a_device->CastVulkan()->GetDevice(), m_textureDescriptorSetLayout, nullptr);
	DEBUG_LOG_INFO("Vulkan DescriptorSetLayout : DescriptorSetLayout Destroyed!\n");
}
