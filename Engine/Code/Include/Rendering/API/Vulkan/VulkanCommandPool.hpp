#pragma once

#include "ICommandPool.hpp"

#include <vulkan/vulkan.h>

#include <Rendering/API/Vulkan/VulkanDevice.hpp>


class VulkanCommandPool final : public ICommandPool
{
public:
	void Create(IDevice* a_device, ISurface* a_surface) override;
	void Destroy() override;

	VulkanCommandPool* CastVulkan() override { return this; }

	[[nodiscard]] VkCommandPool GetCommandPool() const;

private:
	VkCommandPool m_graphicsCommandPool{VK_NULL_HANDLE};
};
