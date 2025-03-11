#pragma once

class IDevice;

class ISynchronisation
{
public:
	virtual ~ISynchronisation() = default;

	virtual void Create() = 0;
	virtual void Destroy() = 0;
};
