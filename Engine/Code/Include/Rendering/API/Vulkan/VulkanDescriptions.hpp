#pragma once

#define GLFW_INCLUDE_VULKAN
#include "IDescriptions.hpp"
#include <vulkan/vulkan.h>

class VulkanDescriptions : public IDescriptions
{
public:
	~VulkanDescriptions() override = default;

	void Create(IDevice* a_device) override;
	void Destroy() override;

	[[nodiscard]] virtual VkDescriptorSetLayout GetInstance() const { return m_descriptorSetLayout; }
	

	VulkanDescriptions* CastVulkan() override { return this; }
private:
	VkDescriptorSetLayout m_descriptorSetLayout{ VK_NULL_HANDLE };
};
