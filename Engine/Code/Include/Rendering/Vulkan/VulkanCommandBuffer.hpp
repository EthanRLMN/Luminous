#pragma once

#include "ICommandBuffer.hpp"
#include "Rendering/Vulkan/VulkanCommandPool.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"

class VulkanCommandBuffer final : public ICommandBuffer
{
public:
	void Create(IDevice* a_device, ICommandPool* a_commandPool) override;
	void Destroy() override;

	[[nodiscard]] std::vector < VkCommandBuffer> GetCommandBuffers() const { return m_commandBuffers; }

	VulkanCommandBuffer* CastVulkan() override
	{
		return this;
	}

	std::vector<VkCommandBuffer> m_commandBuffers{ VK_NULL_HANDLE };
private :
};
