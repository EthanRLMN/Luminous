#include "Logger.hpp"

#include "ICommandPool.hpp"
#include "IDevice.hpp"
#include "IMesh.hpp"
#include "ITexture.hpp"

#include "Struct/VulkanUtilities.hpp"

#include "Rendering/Vulkan/VulkanBuffer.hpp"
#include "Rendering/Vulkan/VulkanCommandPool.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanMesh.hpp"
#include "Rendering/Vulkan/VulkanTexture.hpp"


void VulkanBuffer::Create(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, IDepthResource* a_depthResource, IMesh* a_mesh)
{
    CreateVertexBuffers(a_device, a_texture, a_commandPool, a_depthResource, a_mesh);
    CreateIndexBuffers(a_device, a_texture, a_commandPool, a_depthResource, a_mesh);
	CreateUniformBuffers(a_device, a_texture, a_depthResource);
	DEBUG_LOG_INFO("Vulkan Buffer : Buffer created!\n");
}


void VulkanBuffer::Destroy(IDevice* a_device)
{
	vkDestroyBuffer(a_device->CastVulkan()->GetDevice(), m_indexBuffer, nullptr);
	vkFreeMemory(a_device->CastVulkan()->GetDevice(), m_indexBufferMemory, nullptr);
	vkDestroyBuffer(a_device->CastVulkan()->GetDevice(), m_vertexBuffer, nullptr);
	vkFreeMemory(a_device->CastVulkan()->GetDevice(), m_vertexBufferMemory, nullptr);

	for (const VkBuffer& l_uniformBuffer : m_uniformBuffer)
		vkDestroyBuffer(a_device->CastVulkan()->GetDevice(), l_uniformBuffer, nullptr);

	for (const VkDeviceMemory& l_vkBufferMemory : m_uniformBuffersMemory)
		vkFreeMemory(a_device->CastVulkan()->GetDevice(), l_vkBufferMemory, nullptr);

	DEBUG_LOG_INFO("Vulkan Buffer : Buffer Destroy!\n");
}


void VulkanBuffer::CreateVertexBuffers(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, IDepthResource* a_depthResource, IMesh* a_mesh)
{
	const std::vector<Vertex> l_vertices = a_mesh->CastVulkan()->GetVertices();
	const VkDeviceSize l_bufferSize = sizeof(l_vertices.at(0)) * l_vertices.size();
	VkBuffer l_stagingBuffer { nullptr };
	VkDeviceMemory l_stagingBufferMemory { nullptr };
	a_texture->CastVulkan()->CreateBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), l_bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, l_stagingBuffer, l_stagingBufferMemory, a_depthResource);

	void* l_data = nullptr;
	vkMapMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory, 0, l_bufferSize, 0, &l_data);
	memcpy(l_data, l_vertices.data(), l_bufferSize);
	vkUnmapMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory);

	a_texture->CastVulkan()->CreateBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), l_bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_vertexBuffer, m_vertexBufferMemory, a_depthResource);
	CopyBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetGraphicsQueue(), a_commandPool->CastVulkan()->GetCommandPool(), l_stagingBuffer, m_vertexBuffer, l_bufferSize, a_texture);

	vkDestroyBuffer(a_device->CastVulkan()->GetDevice(), l_stagingBuffer, nullptr);
	vkFreeMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory, nullptr);
}


void VulkanBuffer::CreateIndexBuffers(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, IDepthResource* a_depthResource, IMesh* a_mesh)
{
	const std::vector<uint32_t> l_indices = a_mesh->CastVulkan()->GetIndices();

	const VkDeviceSize l_bufferSize = sizeof(l_indices.at(0)) * l_indices.size();
	VkBuffer l_stagingBuffer { nullptr };
	VkDeviceMemory l_stagingBufferMemory { nullptr };

	a_texture->CastVulkan()->CreateBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), l_bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, l_stagingBuffer, l_stagingBufferMemory, a_depthResource);

	void* l_data = nullptr;
	vkMapMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory, 0, l_bufferSize, 0, &l_data);
	memcpy(l_data, l_indices.data(), l_bufferSize);
	vkUnmapMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory);

	a_texture->CastVulkan()->CreateBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), l_bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_indexBuffer, m_indexBufferMemory, a_depthResource);

	CopyBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetGraphicsQueue(), a_commandPool->CastVulkan()->GetCommandPool(), l_stagingBuffer, m_indexBuffer, l_bufferSize, a_texture);

	vkDestroyBuffer(a_device->CastVulkan()->GetDevice(), l_stagingBuffer, nullptr);
	vkFreeMemory(a_device->CastVulkan()->GetDevice(), l_stagingBufferMemory, nullptr);
}


void VulkanBuffer::CreateUniformBuffers(IDevice* a_device, ITexture* a_texture, IDepthResource* a_depthResource)
{
	m_uniformBuffer.resize(MAX_FRAMES_IN_FLIGHT);
	m_uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
	m_uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
	{
		const VkDeviceSize l_bufferSize = sizeof(UniformBufferObject);
		a_texture->CastVulkan()->CreateBuffer(a_device->CastVulkan()->GetDevice(), a_device->CastVulkan()->GetPhysicalDevice(), l_bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_uniformBuffer[i], m_uniformBuffersMemory[i], a_depthResource);
		vkMapMemory(a_device->CastVulkan()->GetDevice(), m_uniformBuffersMemory[i], 0, l_bufferSize, 0, &m_uniformBuffersMapped[i]);
	}
}


void VulkanBuffer::CopyBuffer(const VkDevice a_device, const VkQueue a_graphicsQueue, const VkCommandPool a_commandPool, const VkBuffer a_srcBuffer, const VkBuffer a_dstBuffer, const VkDeviceSize a_size, ITexture* a_texture)
{
	const VkCommandBuffer l_commandBuffer = a_texture->CastVulkan()->BeginSingleTimeCommands(a_device, a_commandPool);
	VkBufferCopy l_bufferCopy { };
	l_bufferCopy.size = a_size;
	vkCmdCopyBuffer(l_commandBuffer, a_srcBuffer, a_dstBuffer, 1, &l_bufferCopy);

	a_texture->CastVulkan()->EndSingleTimeCommands(a_device, a_graphicsQueue, a_commandPool, l_commandBuffer);
}
