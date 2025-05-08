#pragma once

#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>

#include "IDescriptorSetLayout.hpp"

class VulkanDescriptorSetLayout final : public IDescriptorSetLayout
{
public:
	~VulkanDescriptorSetLayout() override = default;

	void Create(IDevice* a_device) override;
	void Destroy(IDevice* a_device)  override;

	void CreateTextureDescriptorLayout(IDevice* a_device);

	[[nodiscard]] VkDescriptorSetLayout GetDescriptorSetLayout() const { return m_descriptorSetLayout; }
    [[nodiscard]] VkDescriptorSetLayout GetTextureDescriptorSetLayout() const { return m_textureDescriptorSetLayout; }
	VulkanDescriptorSetLayout* CastVulkan() override { return this; }

private:
	VkDescriptorSetLayout m_descriptorSetLayout { nullptr };
    VkDescriptorSetLayout m_textureDescriptorSetLayout{ nullptr };
};
