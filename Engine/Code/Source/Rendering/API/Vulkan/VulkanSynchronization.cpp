#include "Rendering/API/Vulkan/VulkanSynchronization.hpp"

#include <iostream>

#include "Logger.hpp"

void VulkanSynchronization::Create(IDevice* a_device)
{
	m_imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	m_renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	m_fences.resize(MAX_FRAMES_IN_FLIGHT);

	VkSemaphoreCreateInfo l_semaphoreInfo{};
	l_semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo l_fenceInfo{};
	l_fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	l_fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
		if (vkCreateSemaphore(a_device->CastVulkan()->GetDevice(), &l_semaphoreInfo, nullptr, &m_imageAvailableSemaphores[i]) != VK_SUCCESS ||
			vkCreateSemaphore(a_device->CastVulkan()->GetDevice(), &l_semaphoreInfo, nullptr, &m_renderFinishedSemaphores[i]) != VK_SUCCESS ||
			vkCreateFence(a_device->CastVulkan()->GetDevice(), &l_fenceInfo, nullptr, &m_fences[i]) != VK_SUCCESS) {
			std::cout << "failed to create synchronization objects for a frame";
		}
	}
	DEBUG_LOG_INFO("Vulkan Synchronization : Synchronization created!\n");
}

void VulkanSynchronization::Destroy()
{
	DEBUG_LOG_INFO("Vulkan Synchronization : Synchronization destroyed!\n");
}
