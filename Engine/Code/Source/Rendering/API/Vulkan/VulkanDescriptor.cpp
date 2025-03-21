#include "Rendering/API/Vulkan/VulkanDescriptor.hpp"

#include "ITexture.hpp"
#include "Rendering/API/Vulkan/VulkanTexture.hpp"

void VulkanDescriptor::Create(IDevice* a_device, IDescriptionSetLayout* a_descriptionSetLayout, ITexture* a_texture)
{
	CreateDescriptorPool(a_device);
	CreateDescriptorSets(a_device, a_descriptionSetLayout, a_texture);
}

void VulkanDescriptor::Destroy()
{
}

void VulkanDescriptor::CreateDescriptorPool(IDevice* a_device)
{
	std::array<VkDescriptorPoolSize, 2> l_poolSizes{};

	l_poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	l_poolSizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
	l_poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	l_poolSizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	VkDescriptorPoolCreateInfo l_poolInfo{};
	l_poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	l_poolInfo.poolSizeCount = static_cast<uint32_t>(l_poolSizes.size());
	l_poolInfo.pPoolSizes = l_poolSizes.data();
	l_poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	if (vkCreateDescriptorPool(a_device->CastVulkan()->GetDevice(), &l_poolInfo, nullptr, &m_descriptorPool) != VK_SUCCESS)
		DEBUG_LOG_ERROR("Failed to create descriptor pool\n");
}

void VulkanDescriptor::CreateDescriptorSets(IDevice* a_device, IDescriptionSetLayout* a_descriptionSetLayout,
                                            ITexture* a_texture)
{
	const std::vector<VkDescriptorSetLayout> l_layouts(MAX_FRAMES_IN_FLIGHT,
	                                             a_descriptionSetLayout->CastVulkan()->GetDescriptorSetLayout());

	VkDescriptorSetAllocateInfo l_allocateInfo{};

	l_allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	l_allocateInfo.descriptorPool = m_descriptorPool;
	l_allocateInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
	l_allocateInfo.pSetLayouts = l_layouts.data();

	m_descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
	if (vkAllocateDescriptorSets(a_device->CastVulkan()->GetDevice(), &l_allocateInfo, m_descriptorSets.data()) != VK_SUCCESS)
		DEBUG_LOG_ERROR("failed to allocate descriptor sets !\n");

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
	{
		VkDescriptorBufferInfo l_bufferInfo{};
		l_bufferInfo.buffer = uniformBuffer[i];
		l_bufferInfo.offset = 0;
		l_bufferInfo.range = sizeof(UniformBufferObject);

		VkDescriptorImageInfo l_imageInfo{};
		l_imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		l_imageInfo.imageView = a_texture->CastVulkan()->GetTextureImageView();
		l_imageInfo.sampler = a_texture->CastVulkan()->GetTextureSampler();

		std::array<VkWriteDescriptorSet, 2> l_descriptorWrites{};
		l_descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
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

		vkUpdateDescriptorSets(a_device->CastVulkan()->GetDevice(), static_cast<uint32_t>(l_descriptorWrites.size()),
		                       l_descriptorWrites.data(), 0, nullptr);
	}
}
