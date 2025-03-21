#pragma once

#include "ISynchronization.hpp"
#include <vulkan/vulkan.hpp>
#include "Struct/VulkanUtilities.hpp"

class VulkanSynchronization final : public ISynchronization
{
public:
	void Create(IDevice* a_device) override;
	void Destroy() override;

	VulkanSynchronization* CastVulkan() override { return this; }

private:

};
