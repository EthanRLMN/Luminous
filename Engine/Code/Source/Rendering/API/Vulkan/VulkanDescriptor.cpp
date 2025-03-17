#include <array>

#include "Rendering/API/Vulkan/VulkanDescriptor.hpp"
#include "Rendering/API/Vulkan/VulkanDevice.hpp"

void VulkanDescriptor::Create(IDevice* a_device)
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

	VkDescriptorSetLayoutCreateInfo l_layoutInfo{};
	l_layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	l_layoutInfo.bindingCount = static_cast<uint32_t>(l_bindings.size());
	l_layoutInfo.pBindings = l_bindings.data();

	//Create Descriptor SetLayout
	const VkResult l_result = vkCreateDescriptorSetLayout(a_device->CastVulkan()->GetDevice(), &l_layoutInfo, nullptr,
	                                                      &m_descriptorSetLayout);
	if (l_result != VK_SUCCESS)
		std::cout << "Failed to create a descriptor set layout";
}

void VulkanDescriptor::Destroy()
{
}
