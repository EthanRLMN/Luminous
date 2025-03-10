#pragma once
#include "Rendering/ISynchronisation.hpp"

class VulkanSynchronisation : public ISynchronisation
{
	void Create() override;
	void Destroy() override;
};
