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

	VkDescriptorSetLayoutBinding l_lightLayoutBinding = {};
    l_samplerLayoutBinding.binding = 2;
    l_samplerLayoutBinding.descriptorCount = 1;
    l_samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    l_samplerLayoutBinding.pImmutableSamplers = nullptr;
    l_samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;


	const std::array<VkDescriptorSetLayoutBinding, 3> l_bindings = { l_uboLayoutBinding, l_samplerLayoutBinding, l_lightLayoutBinding };
	VkDescriptorSetLayoutCreateInfo l_layoutInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
	l_layoutInfo.bindingCount = static_cast<uint32_t>(l_bindings.size());
	l_layoutInfo.pBindings = l_bindings.data();

	const VkResult l_result = vkCreateDescriptorSetLayout(a_device->CastVulkan()->GetDevice(), &l_layoutInfo, nullptr, &m_descriptorSetLayout);
	if (l_result != VK_SUCCESS)
		DEBUG_LOG_ERROR("Vulkan Descriptor : Failed to create a descriptor set layout!\n");

	DEBUG_LOG_INFO("Vulkan DescriptorSetLayout : DescriptorSetLayout Created!\n");


	// LIGHT EDIT 99
	/*
	VkDescriptorSetLayoutBinding l_lightBinding = {};
    l_lightBinding.binding = 0;
    l_lightBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    l_lightBinding.descriptorCount = 1;
    l_lightBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    l_lightBinding.pImmutableSamplers = nullptr;

    const std::array<VkDescriptorSetLayoutBinding, 1> l_lightBindings = { l_lightBinding };
    VkDescriptorSetLayoutCreateInfo l_lightLayoutInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
    l_lightLayoutInfo.bindingCount = static_cast<uint32_t>(l_lightBindings.size());
    l_lightLayoutInfo.pBindings = l_lightBindings.data();

    const VkResult l_lightResult = vkCreateDescriptorSetLayout(a_device->CastVulkan()->GetDevice(), &l_lightLayoutInfo, nullptr, &m_lightDescriptorSetLayout);
    if (l_lightResult != VK_SUCCESS)
        DEBUG_LOG_ERROR("Vulkan Descriptor : Failed to create a light descriptor set layout!\n");*/

}

void VulkanDescriptorSetLayout::Destroy(IDevice* a_device)
{
	vkDestroyDescriptorSetLayout(a_device->CastVulkan()->GetDevice(), m_descriptorSetLayout, nullptr);
    vkDestroyDescriptorSetLayout(a_device->CastVulkan()->GetDevice(), m_lightDescriptorSetLayout, nullptr);
	DEBUG_LOG_INFO("Vulkan DescriptorSetLayout : DescriptorSetLayout Destroyed!\n");
}
