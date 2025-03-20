#include "Rendering/API/Vulkan/VulkanBuffer.hpp"
#include "Logger.hpp"

void VulkanBuffer::Create(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, IDepthResource* a_depthResource)
{
	DEBUG_LOG_INFO("Vulkan Buffer : Buffer created!\n");
	CreateVertexBuffers(a_device, a_texture, a_commandPool, a_depthResource);
	CreateIndexBuffers(a_device, a_texture, a_commandPool, a_depthResource);
	CreateUniformBuffers(a_device, a_texture, a_depthResource);

}

void VulkanBuffer::Destroy()
{
	DEBUG_LOG_ERROR("Vulkan Buffer : Buffer created!\n");
}

void VulkanBuffer::CreateVertexBuffers(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, IDepthResource* a_depthResource)
{
	/*
	VkDeviceSize l_bufferSize = sizeof(vulkanVertices[0]) * vulkanVertices.size();
	VkBuffer l_stagingBuffer;
	VkDeviceMemory l_stagingBufferMemory;


	a_texture->CastVulkan()->CreateBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), l_bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, l_stagingBuffer, l_stagingBufferMemory, a_depthResource);

	void* l_data;
	vkMapMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory, 0, l_bufferSize, 0, &l_data);
	memcpy(l_data, vulkanVertices.data(), (size_t)l_bufferSize);
	vkUnmapMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory);

	a_texture->CastVulkan()->CreateBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), l_bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory, a_depthResource);

	CopyBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetGraphicsQueue(), a_commandPool->CastVulkan()->GetCommandPool(), l_stagingBuffer, vertexBuffer, l_bufferSize, a_texture);


	vkDestroyBuffer(a_device->CastVulkan()->GetDevice(), l_stagingBuffer, nullptr);
	vkFreeMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory, nullptr);*/
}

void VulkanBuffer::CreateIndexBuffers(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, IDepthResource* a_depthResource)
{
	/*
	VkDeviceSize l_bufferSize = sizeof(vulkanIndices[0]) * vulkanIndices.size();
	VkBuffer l_stagingBuffer;
	VkDeviceMemory l_stagingBufferMemory;

	a_texture->CastVulkan()->CreateBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), l_bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, l_stagingBuffer, l_stagingBufferMemory, a_depthResource);

	void* l_data;
	vkMapMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory, 0, l_bufferSize, 0, &l_data);
	memcpy(l_data, vulkanIndices.data(), (size_t)l_bufferSize);
	vkUnmapMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory);

	a_texture->CastVulkan()->CreateBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), l_bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory, a_depthResource);

	CopyBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetGraphicsQueue(), a_commandPool->CastVulkan()->GetCommandPool(), l_stagingBuffer, indexBuffer, l_bufferSize, a_texture);

	vkDestroyBuffer(a_device->CastVulkan()->GetDevice(), l_stagingBuffer, nullptr);
	vkFreeMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory, nullptr);*/
}

void VulkanBuffer::CreateUniformBuffers(IDevice* a_device, ITexture* a_texture, IDepthResource* a_depthResource)
{
	/*
	VkDeviceSize l_bufferSize = sizeof(UniformBufferObject);

	uniformBuffer.resize(MAX_FRAMES_IN_FLIGHT);
	uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
	uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
		a_texture->CastVulkan()->CreateBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), l_bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffer[i], uniformBuffersMemory[i], a_depthResource);
		vkMapMemory(a_device->CastVulkan()->GetDevice(), uniformBuffersMemory[i], 0, l_bufferSize, 0, &uniformBuffersMapped[i]);
	}*/
}
