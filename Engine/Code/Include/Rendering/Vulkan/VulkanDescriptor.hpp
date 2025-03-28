#pragma once

#include <array>
#include <vulkan/vulkan.hpp>

#include "IBuffer.hpp"
#include "IDescriptor.hpp"

#include "Rendering/Vulkan/VulkanDescriptorSetLayout.hpp"

class VulkanDescriptor final : public IDescriptor
{
public:
	void Create(IDevice* a_device, IDescriptorSetLayout* a_descriptorSetLayout, ITexture* a_texture, IBuffer* a_buffer) override;
	void Destroy(IDevice* a_device) override;

	[[nodiscard]] VkDescriptorPool GetDescriptorPool() const { return m_descriptorPool; }
	[[nodiscard]] std::vector<VkDescriptorSet> GetDescriptorSet() const { return m_descriptorSets; };

	VulkanDescriptor* CastVulkan() override { return this; }

private:
	void CreateDescriptorPool(IDevice* a_device);
	void CreateDescriptorSets(IDevice* a_device, IDescriptorSetLayout* a_descriptorSetLayout, ITexture* a_texture);
	void SetBuffers(IBuffer* a_buffer);
	

	VkDescriptorPool m_descriptorPool{VK_NULL_HANDLE};
	std::vector<VkDescriptorSet> m_descriptorSets{VK_NULL_HANDLE};

	std::vector<VkBuffer> m_uniformBuffer{VK_NULL_HANDLE};
	std::vector<VkDeviceMemory> m_uniformBuffersMemory{VK_NULL_HANDLE};
	std::vector<void*> m_uniformBuffersMapped{VK_NULL_HANDLE};
};
