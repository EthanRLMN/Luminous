#pragma once

class IDevice;
class IRenderPass;
class ISwapChain;
class IPipeline;

class IBuffer
{
public:
	virtual ~IBuffer() = default;

	virtual void Create() = 0;
	virtual void Destroy() = 0;
};
