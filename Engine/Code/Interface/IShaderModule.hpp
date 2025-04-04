#pragma once

#include <vector>

class IDevice;

class ShaderModule
{
public:
	
	ShaderModule() = default;
    ~ShaderModule() = default;

	virtual bool Create(IDevice* a_device, const std::vector<char*> a_shaders) = 0;
    virtual void Destroy()

};
