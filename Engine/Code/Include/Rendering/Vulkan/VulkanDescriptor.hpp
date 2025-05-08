#pragma once
#include <vulkan/vulkan.h>

#include "IBuffer.hpp"
#include "IDescriptor.hpp"

class VulkanDescriptor final : public IDescriptor
{
public:
	void Create(IDevice* a_device, IDescriptorSetLayout* a_descriptorSetLayout, IBuffer* a_buffer) override;
	void Destroy(IDevice* a_device) override;

	[[nodiscard]] VkDescriptorPool GetDescriptorPool() const { return m_descriptorPool; }
	[[nodiscard]] VkDescriptorPool GetImGUIDescriptorPool() const { return m_imguiDescriptorPool; }
	[[nodiscard]] std::vector<VkDescriptorSet> GetDescriptorSet() const { return m_descriptorSets; };
    [[nodiscard]] VkDescriptorSet GetLightDescriptorSet() const { return m_lightDescriptorSets; };
	VulkanDescriptor* CastVulkan() override { return this; }
    void UpdateDescriptorSets(IDevice* a_device) const;

private:
	void CreateDescriptorPool(IDevice* a_device);
    void CreateImGUIDescriptorPool(IDevice* a_device);
	void CreateDescriptorSets(IDevice* a_device, IDescriptorSetLayout* a_descriptorSetLayout);
	void SetBuffers(IBuffer* a_buffer);
	

	VkDescriptorPool m_descriptorPool { nullptr };
	VkDescriptorPool m_imguiDescriptorPool { nullptr };
	std::vector<VkDescriptorSet> m_descriptorSets { nullptr };

	std::vector<VkBuffer> m_uniformBuffer { nullptr };
	std::vector<VkDeviceMemory> m_uniformBuffersMemory { nullptr };
	std::vector<void*> m_uniformBuffersMapped { nullptr };

	std::vector<VkBuffer> m_lightUniformBuffer{ nullptr };
    std::vector<VkDeviceMemory> m_lightUniformBuffersMemory{ nullptr };
    std::vector<void*> m_lightUniformBuffersMapped{ nullptr };


	//VkDescriptorPool m_lightDescriptorPool{ nullptr };
    VkDescriptorSet m_lightDescriptorSets{ nullptr };
};
