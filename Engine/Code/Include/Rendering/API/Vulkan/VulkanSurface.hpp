#pragma once

#include <vulkan/vulkan.h>

#include "ISurface.hpp"

class VulkanSurface final : public ISurface
{
public:
	void Create(IInstance* a_instance, IWindow* a_window) override;
	void Destroy(IInstance* a_instance) override;

	[[nodiscard]] VkSurfaceKHR GetSurface() const { return m_surface; }

	VulkanSurface* CastVulkan() override { return this; }

private:
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;
};

