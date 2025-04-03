#pragma once

#include <vulkan/vulkan.h>

#include "ICommandPool.hpp"

class VulkanCommandPool final : public ICommandPool
{
public:
	void Create(IDevice* a_device, ISurface* a_surface) override;
	void Destroy(IDevice* a_device) override;

	VulkanCommandPool* CastVulkan() override { return this; }

	[[nodiscard]] VkCommandPool GetCommandPool() const { return m_graphicsCommandPool; }


private:
	VkCommandPool m_graphicsCommandPool{ nullptr };
};
