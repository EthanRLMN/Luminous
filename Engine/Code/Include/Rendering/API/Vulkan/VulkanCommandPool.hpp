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

	virtual VulkanCommandPool* CastVulkan()
	{
		std::cout << "Wrong cast\n";
		return nullptr;
	}
private:
	VkCommandPool m_graphicsCommandPool{ VK_NULL_HANDLE };
};
