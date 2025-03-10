#pragma once

#include "Rendering/IPipeline.hpp"

class VulkanPipeline : public IPipeline
{
public:
	void Create() override;
	void Destroy() override;
};
