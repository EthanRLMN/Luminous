#pragma once

#include "ISwapChain.hpp"
#include "VulkanSurface.hpp"

class VulkanSwapChain : public ISwapChain
{
public:
	void Create(IWindow* a_window, IDevice* a_device, ISurface* a_surface) override;

	void Destroy(IDevice* a_device) override;
};
