#pragma once

#include <iostream>

class IInstance;
class ISurface;
class Window;

class IDevice
{
public:
    virtual ~IDevice() = default;

    virtual void Create(IInstance* a_instance, Window* a_window, ISurface* a_surface) = 0;

    virtual void Destroy() = 0;

    virtual IDevice* CastVulkan()
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
