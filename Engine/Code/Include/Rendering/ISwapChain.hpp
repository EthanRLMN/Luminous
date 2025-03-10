#pragma once

class Window;
class IDevice;
class ISurface;
class IBuffer;
class IRenderPass;

class ISwapChain
{
public:
	virtual ~ISwapChain() = default;

	virtual void Create(Window* a_window, IDevice* a_device, ISurface* a_surface) = 0;

	virtual void Destroy(IDevice* a_device) = 0;
};
