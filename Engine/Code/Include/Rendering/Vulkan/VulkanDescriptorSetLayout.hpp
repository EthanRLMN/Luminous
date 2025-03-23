#pragma once

#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>

#include "IDescriptorSetLayout.hpp"

class VulkanDescriptorSetLayout final : public IDescriptorSetLayout
{
public:
	~VulkanDescriptorSetLayout() override = default;

	void Create(IDevice* a_device) override;
	void Destroy() override;

	[[nodiscard]] VkDescriptorSetLayout GetDescriptorSetLayout() const { return m_descriptorSetLayout; }
	VulkanDescriptorSetLayout* CastVulkan() override { return this; }

private:
	VkDescriptorSetLayout m_descriptorSetLayout { VK_NULL_HANDLE };
};
