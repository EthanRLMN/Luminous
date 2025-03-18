#pragma once

#include "IBuffer.hpp"

class VulkanBuffer final : public IBuffer
{
public:
	VulkanBuffer() = default;

	void Create() override;
	void Destroy() override;

};
