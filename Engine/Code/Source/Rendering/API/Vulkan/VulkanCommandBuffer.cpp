#include "Rendering/API/Vulkan/VulkanCommandBuffer.hpp"

void VulkanCommandBuffer::Create(IDevice* a_device, ISwapChain* a_swapChain, ICommandPool* a_commandPool)
{
	a_swapChain->CastVulkan()->GetCommandBuffers().resize(MAX_FRAMES_IN_FLIGHT);

	VkCommandBufferAllocateInfo l_allocateInfo{};
	l_allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	l_allocateInfo.commandPool = a_commandPool->CastVulkan()->GetCommandPool();
	l_allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	l_allocateInfo.commandBufferCount = static_cast<uint32_t>(a_swapChain->CastVulkan()->GetCommandBuffers().size());

	if (vkAllocateCommandBuffers(a_device->CastVulkan()->GetDevice(), &l_allocateInfo,
	                             a_swapChain->CastVulkan()->GetCommandBuffers().data()) != VK_SUCCESS)
		DEBUG_LOG_ERROR("Failed to allocate command Buffer!\n");
}

void VulkanCommandBuffer::Destroy()
{
}
