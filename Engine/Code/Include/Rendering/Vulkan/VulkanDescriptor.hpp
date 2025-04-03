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
	void UpdateDescriptorSets(IDevice* a_device, ITexture* a_texture);

	VkDescriptorPool m_descriptorPool { nullptr };
	std::vector<VkDescriptorSet> m_descriptorSets { nullptr };

	std::vector<VkBuffer> m_uniformBuffer { nullptr };
	std::vector<VkDeviceMemory> m_uniformBuffersMemory { nullptr };
	std::vector<void*> m_uniformBuffersMapped { nullptr };
};
