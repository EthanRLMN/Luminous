#pragma once
#include "../../LantualBuffer.h"
#include <vulkan/vulkan.h>
#include <vector>

class LantualVkBuffer : public LantualBuffer
{
public:
	LantualVkBuffer() = default;
	~LantualVkBuffer() = default;

	void Create() override;
	void Destroy() override;

};