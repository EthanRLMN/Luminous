#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "IPipeline.hpp"

class VulkanPipeline final : public IPipeline
{
public:
	void Create(IDevice* a_device, IRenderPass* a_renderPass, IDescriptorSetLayout* a_descriptionSetLayout) override;
	void Destroy(IDevice* a_device) override;

	[[nodiscard]] VkPipeline GetGraphicsPipeline() const { return m_graphicsPipeline; }
	[[nodiscard]] VkPipelineLayout GetPipelineLayout() const { return m_pipelineLayout; };

	VulkanPipeline* CastVulkan() override { return this; }
	VkShaderModule CreateShaderModule(VkDevice a_device, const std::vector<char>& a_code);

private:

	VkPipeline m_graphicsPipeline{ VK_NULL_HANDLE };
	VkPipelineLayout m_pipelineLayout{ VK_NULL_HANDLE };
};
