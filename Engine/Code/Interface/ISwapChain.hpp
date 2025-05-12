#pragma once

#include "Vector2.hpp"

class VulkanSwapChain;
class IWindow;
class IDevice;
class ISurface;
class IBuffer;
class IRenderPass;

class ISwapChain
{
public:
	virtual ~ISwapChain() = default;

	virtual void Create(IWindow* a_window, IDevice* a_device, ISurface* a_surface) = 0;
	virtual void Destroy(IDevice* a_device) = 0;
    [[nodiscard]] virtual Maths::Vector2 GetSize() const = 0;

	virtual VulkanSwapChain* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan SwapChain : Cast is Wrong!\n");
		return nullptr;
	}
};
