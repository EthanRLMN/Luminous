#pragma once

#include <iostream>

class LantualInstance;
class LantualSurface;
class Window;

class LantualDevice {
public:

	virtual ~LantualDevice() = default;

	virtual void Create(LantualInstance* _instance, Window* _window ,LantualSurface* _surface) = 0;
	virtual void Destroy() = 0;

    virtual LantualDevice* CastVulkan()
    {
        std::cout << "Wrong cast" << std::endl;
        return nullptr;
    }
    /*
    virtual VkDevice GetDevice() const
    {
        return nullptr;
    }*/


    
};