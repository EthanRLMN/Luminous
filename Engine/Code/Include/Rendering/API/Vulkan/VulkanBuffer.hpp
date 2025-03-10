#pragma once

#include "Rendering/IBuffer.hpp"

class VulkanBuffer : public IBuffer
{
public:
	VulkanBuffer() = default;
	~VulkanBuffer() = default;

	void Create() override;
	void Destroy() override;

};
