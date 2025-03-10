#pragma once

class IDevice;
class IRenderPass;


class IPipeline
{
public:
	virtual ~IPipeline() = default;

	virtual void Create() = 0;
	virtual void Destroy() = 0;
};
