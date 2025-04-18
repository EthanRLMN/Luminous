#pragma once

#include "Logger.hpp"

enum class MULTISAMPLING_SAMPLES;
class VulkanMultiSampling;
class IDevice;
class ISwapChain;


class IMultiSampling
{
public:
    virtual ~IMultiSampling() = default;

    virtual void Create(IDevice* a_device, ISwapChain* a_swapchain) = 0;
    virtual void Destroy(IDevice* a_device) = 0;

    virtual void SetSampleCount(IDevice* a_device, const MULTISAMPLING_SAMPLES& a_samples) = 0;

    virtual VulkanMultiSampling* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan MultiSampling : Cast is Wrong!\n");
        return nullptr;
    }
};
