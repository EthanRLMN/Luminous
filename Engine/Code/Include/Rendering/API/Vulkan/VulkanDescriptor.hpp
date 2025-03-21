#pragma once
#include "IDescriptor.hpp"
#include <array>
#include <vulkan/vulkan.hpp>
#include "Struct/VulkanUtilities.hpp"
#include "Rendering/API/Vulkan/VulkanDevice.hpp"
#include "Rendering/API/Vulkan/VulkanDescriptionSetLayout.hpp"


class VulkanDescriptor final : public IDescriptor {

public:
	void Create(IDevice* a_device, IDescriptionSetLayout* a_descriptionSetLayout) override;
	void Destroy() override;

	[[nodiscard]] VkDescriptorPool GetDescriptorPool() const { return m_descriptorPool; }
	[[nodiscard]] std::vector<VkDescriptorSet> GetDescriptorSet() const { return m_descriptorSets; };

	VulkanDescriptor* CastVulkan() override { return this; }

private:
	void CreateDescriptorPool(IDevice* a_device);
	void CreateDescriptorSets(IDevice* a_device, IDescriptionSetLayout* a_descriptionSetLayout);

	VkDescriptorPool m_descriptorPool{ VK_NULL_HANDLE };
	std::vector<VkDescriptorSet> m_descriptorSets{ VK_NULL_HANDLE };
};