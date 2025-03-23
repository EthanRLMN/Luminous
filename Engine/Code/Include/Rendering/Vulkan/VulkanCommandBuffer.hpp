#pragma once

#include "ICommandBuffer.hpp"
#include "Rendering/Vulkan/VulkanCommandPool.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"

class VulkanCommandBuffer final : public ICommandBuffer
{
public:
	void Create(IDevice* a_device, ISwapChain* a_swapChain, ICommandPool* a_commandPool) override;
	void Destroy() override;

	VulkanCommandBuffer* CastVulkan() override
	{
		return this;
	}
};
