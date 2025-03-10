#pragma once
#include <vulkan/vulkan.h>
#include "../../LantualRenderPass.h"
#include <iostream>
#include <stdexcept> //error checker
#include <vector>
#include <set>
#include <algorithm>
#include <array>


class LantualVkRenderPass : public LantualRenderPass {
public :
	void Create(LantualSwapChain* _swapchain, LantualDevice* _device) override;
	void Destroy(LantualDevice* _device) override;


private:
	VkRenderPass renderPass = VK_NULL_HANDLE;
};
