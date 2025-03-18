#pragma once

#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>
#include "IDescriptions.hpp"

class VulkanDescriptor final : public IDescriptor
{
public:
	~VulkanDescriptor() override = default;

	void Create(IDevice* a_device) override;
	void Destroy() override;

	[[nodiscard]] virtual VkDescriptorSetLayout GetInstance() const { return m_descriptorSetLayout; }

	VulkanDescriptor* CastVulkan() override { return this; }

private:
	VkDescriptorSetLayout m_descriptorSetLayout { VK_NULL_HANDLE };
};
