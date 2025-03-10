#pragma once

#include <iostream>

class LantualDevice;
class LantualRenderPass;
class LantualSwapChain;
class LantualPipeline;

class LantualBuffer {

public:
	virtual void Create() = 0;
	virtual void Destroy() = 0;

};
