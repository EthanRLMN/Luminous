#pragma once

#include "ISynchronization.hpp"

class VulkanSynchronization final : public ISynchronization
{
	void Create() override;
	void Destroy() override;
};
