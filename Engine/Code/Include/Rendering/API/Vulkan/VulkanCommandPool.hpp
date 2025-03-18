#pragma once
#include <vulkan/vulkan.h>

#include "ICommandPool.hpp"
#include <Rendering/API/Vulkan/VulkanDevice.hpp>
#include <Rendering/API/Vulkan/VulkanSurface.hpp>

#include "Struct/VulkanUtilities.hpp"
#include "Utilities.hpp"



class VulkanCommandPool : public ICommandPool
{
public:
	void Create(IDevice* a_device , ISurface* a_surface) override;
	void Destroy() override;

	VulkanCommandPool* CastVulkan() override { return this; }

	[[nodiscard]] VkCommandPool GetCommandPool() const;

private:
	VkCommandPool m_graphicsCommandPool{ VK_NULL_HANDLE };
};
