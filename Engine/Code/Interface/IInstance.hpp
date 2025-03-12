#pragma once
#include <iostream>

class VulkanInstance;
class EWindow;

class IInstance
{
public:
    virtual ~IInstance() = default;

    virtual void Create(EWindow* a_window) = 0;
    virtual void Destroy() = 0;

    virtual VulkanInstance* CastVulkan()
    {
        std::cout << "Wrong cast\n";
        return nullptr;
    }
};
