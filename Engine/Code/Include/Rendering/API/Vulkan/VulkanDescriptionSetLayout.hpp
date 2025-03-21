#pragma once

#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>
#include "IDescriptionSetLayout.hpp"

class VulkanDescriptionSetLayout final : public IDescriptionSetLayout
{
public:
	~VulkanDescriptionSetLayout() override = default;

	void Create(IDevice* a_device) override;
	void Destroy() override;

	[[nodiscard]] virtual VkDescriptorSetLayout GetInstance() const { return m_descriptorSetLayout; }

	VulkanDescriptionSetLayout* CastVulkan() override { return this; }

private:
	VkDescriptorSetLayout m_descriptorSetLayout { VK_NULL_HANDLE };
};
