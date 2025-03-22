#pragma once

#include "Logger.hpp"

class VulkanPipeline;
class IDevice;
class IRenderPass;
class IDescriptorSetLayout;


class IPipeline
{
public:
	virtual ~IPipeline() = default;

	virtual void Create(IDevice* a_device,IRenderPass* a_renderpass, IDescriptorSetLayout* a_descriptionSetLayout) = 0;
	virtual void Destroy() = 0;

	virtual VulkanPipeline* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Pipeline : Cast is Wrong!\n");
		return nullptr;
	}
};
