#pragma once

#include "IBuffer.hpp"

class VulkanBuffer : public IBuffer
{
public:
	VulkanBuffer() = default;

	void Create() override;
	void Destroy() override;

};
