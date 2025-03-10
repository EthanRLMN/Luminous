#pragma once
#include <iostream>

class VulkanSurface;
class LantualInstance;
class Window;



class LantualSurface {
public:
	virtual ~LantualSurface() = default;

	virtual void Create(LantualInstance* _instance, Window* _window) = 0;
	virtual void Destroy(LantualInstance* _intance)  = 0 ;


	virtual LantualSurface* CastVulkan()
	{
		std::cout << "Wrong cast" << std::endl;
		return nullptr;
	}

	virtual VkSurfaceKHR GetSurface() const
	{
		return nullptr;
	}

};
