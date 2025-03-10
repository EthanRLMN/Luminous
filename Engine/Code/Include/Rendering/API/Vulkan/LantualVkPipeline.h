#pragma once
#include "../../LantualPipeline.h"
#include <iostream>
#include <stdexcept> //error checker
#include <vector>
#include <set>
#include <algorithm>
#include <array>
#include <vulkan/vulkan.h>

class LantualVkPipeline :public LantualPipeline
{
public:
	void Create() override;
	void Destroy() override;
};
