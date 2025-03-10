#pragma once
#include <iostream>
#include <vector>


class Window;
class LantualDevice;
class LantualSurface;
class LantualBuffer;
class LantualRenderPass;

class LantualSwapChain {
public:

	virtual void Create(Window* _window,LantualDevice* _device, LantualSurface* _surface) = 0;
	virtual void Destroy(LantualDevice* _device) = 0;

};