#include "ICommandPool.hpp"
#include "IDevice.hpp"

#include "Rendering/Vulkan/VulkanCommandBuffer.hpp"
#include "Rendering/Vulkan/VulkanCommandPool.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"


void VulkanCommandBuffer::Create(IDevice* a_device, ICommandPool* a_commandPool)
{
	m_commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

	VkCommandBufferAllocateInfo l_allocateInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
	l_allocateInfo.commandPool = a_commandPool->CastVulkan()->GetCommandPool();
	l_allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	l_allocateInfo.commandBufferCount = static_cast<uint32_t>(m_commandBuffers.size());

	if (vkAllocateCommandBuffers(a_device->CastVulkan()->GetDevice(), &l_allocateInfo, m_commandBuffers.data()) != VK_SUCCESS)
		DEBUG_LOG_ERROR("Failed to allocate command Buffer!\n");
}

