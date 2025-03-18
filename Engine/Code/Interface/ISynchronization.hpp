#pragma once

class IDevice;

class ISynchronization
{
public:
	virtual ~ISynchronization() = default;

	virtual void Create() = 0;
	virtual void Destroy() = 0;
};
