#pragma once
#include <iostream>

class VulkanDescriptions;
class IDevice;

class IDescriptions
{
public:
    virtual ~IDescriptions() = default;

    virtual void Create(IDevice* a_device) = 0;
    virtual void Destroy() = 0;

    virtual VulkanDescriptions* CastVulkan()
    {
        std::cout << "Wrong cast\n";
        return nullptr;
    }
};
