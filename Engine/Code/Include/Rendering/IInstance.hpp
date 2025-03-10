#pragma once
#include <iostream>

class VulkanInstance;
class Window;

class IInstance
{
public:
    virtual ~IInstance() = default;

    virtual void Create(Window* _window) = 0;
    virtual void Destroy() = 0;

    virtual VulkanInstance* CastVulkan()
    {
        std::cout << "Wrong cast" << std::endl;
        return nullptr;
    }
};
