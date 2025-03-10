#pragma once
#include "../../LantualSwapChain.h"
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include <algorithm>

class LantualVkSwapChain : public LantualSwapChain {
public:
	void Create(Window* _window, LantualDevice* _device, LantualSurface* _surface) override;
	void Destroy(LantualDevice* _device) override;
};