#pragma once

#include "VulkanSurface.hpp"
#include "Rendering/ISwapChain.hpp"

class VulkanSwapChain : public ISwapChain
{
public:
	void Create(Window* a_window, IDevice* a_device, ISurface* a_surface) override;

	void Destroy(IDevice* a_device) override;
};
