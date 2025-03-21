#pragma once
#include "IDescriptor.hpp"
#include <array>
#include <vulkan/vulkan.hpp>
#include "Struct/VulkanUtilities.hpp"
#include "Rendering/API/Vulkan/VulkanDevice.hpp"
#include "Rendering/API/Vulkan/VulkanDescriptionSetLayout.hpp"
#include "Rendering/API/Vulkan/VulkanTexture.hpp"



class VulkanDescriptor final : public IDescriptor {

public:
	void Create(IDevice* a_device, IDescriptionSetLayout* a_descriptionSetLayout, ITexture* a_texture) override;
	void Destroy() override;

	[[nodiscard]] VkDescriptorPool GetDescriptorPool() const { return m_descriptorPool; }
	[[nodiscard]] std::vector<VkDescriptorSet> GetDescriptorSet() const { return m_descriptorSets; };

	VulkanDescriptor* CastVulkan() override { return this; }

private:
	void CreateDescriptorPool(IDevice* a_device);
	void CreateDescriptorSets(IDevice* a_device, IDescriptionSetLayout* a_descriptionSetLayout, ITexture* a_texture);

	VkDescriptorPool m_descriptorPool{ VK_NULL_HANDLE };
	std::vector<VkDescriptorSet> m_descriptorSets{ VK_NULL_HANDLE };

	std::vector<VkBuffer> uniformBuffer{ VK_NULL_HANDLE };
	std::vector<VkDeviceMemory> uniformBuffersMemory{ VK_NULL_HANDLE };
	std::vector<void*> uniformBuffersMapped{ VK_NULL_HANDLE };
};