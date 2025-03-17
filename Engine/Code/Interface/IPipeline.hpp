#pragma once
#include <iostream>

class VulkanPipeline;
class IDevice;
class IRenderPass;
class IDescriptor;


class IPipeline
{
public:
	virtual ~IPipeline() = default;

	virtual void Create(IDevice* a_device,IRenderPass* a_renderpass, IDescriptor* a_descriptor) = 0;
	virtual void Destroy() = 0;

	virtual VulkanPipeline* CastVulkan()
	{
		std::cout << "Wrong cast\n";
		return nullptr;
	}
};
