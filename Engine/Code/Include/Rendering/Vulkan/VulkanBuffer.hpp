#pragma once

#include "IBuffer.hpp"
#include "vk_mem_alloc.h"

class VulkanMemoryAllocator;

class VulkanBuffer final : public IBuffer
{
public:
	VulkanBuffer() = default;

	void Create(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool,
	            IDepthResource* a_depthResource) override;
	void Init(size_t a_size, VkBufferUsageFlags a_usage, VmaMemoryUsage a_memUsage, VmaAllocator a_memAllocator);
	void SendData(const void* a_data, size_t a_size) override;
	void Destroy() override;

	VulkanBuffer* CastVulkan() override { return this; }

private:
	void CreateVertexBuffers(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool,
	                         IDepthResource* a_depthResource);
	void CreateIndexBuffers(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool,
	                        IDepthResource* a_depthResource);
	void CreateUniformBuffers(IDevice* a_device, ITexture* a_texture, IDepthResource* a_depthResource);

	VkBuffer m_buffer = VK_NULL_HANDLE;
	VmaAllocation m_allocation = VK_NULL_HANDLE;
	VmaAllocator m_allocator = VK_NULL_HANDLE;
};
