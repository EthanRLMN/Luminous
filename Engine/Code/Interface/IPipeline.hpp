#pragma once

#include "Logger.hpp"

class VulkanPipeline;
class IDevice;
class IRenderPass;
class IDescriptorSetLayout;
class IMultiSampling;

class IResourceManager;
class IPipeline
{
public:
	virtual ~IPipeline() = default;

	virtual void Create(IDevice* a_device, IRenderPass* a_renderPass, IDescriptorSetLayout* a_descriptionSetLayout, IResourceManager* a_resourceManager) = 0;
	virtual void Destroy(IDevice* a_device) = 0;

	virtual VulkanPipeline* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Pipeline : Cast is Wrong!\n");
		return nullptr;
	}
};
