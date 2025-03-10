#pragma once
#include <iostream>

class LantualVkRenderPass;
class LantualSwapChain;
class LantualDevice;

class LantualRenderPass {
public:
	virtual ~LantualRenderPass() = default;
	virtual void Create(LantualSwapChain* _swapchain, LantualDevice* _device) = 0;
	virtual void Destroy(LantualDevice* _device) = 0;

};
