#pragma once

#include "Logger.hpp"

class VulkanMultiSampling;
class IDevice;
class ISwapChain;

enum class SamplingCount
{
    MSAA_SAMPLECOUNT_1 = 1,
    MSAA_SAMPLECOUNT_2 = 2,
    MSAA_SAMPLECOUNT_4,
    MSAA_SAMPLECOUNT_8,
    MSAA_SAMPLECOUNT_16,
    MSAA_SAMPLECOUNT_32,
    MSAA_SAMPLECOUNT_64
};



class IMultiSampling
{
public:
    virtual ~IMultiSampling() = default;

    virtual void Create(IDevice* a_device, ISwapChain* a_swapchain) = 0;
    virtual void Destroy(IDevice* a_device) = 0;

    virtual void SetSampleCount(IDevice* a_device, const SamplingCount& a_samplingCount) = 0;

    virtual VulkanMultiSampling* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan MultiSampling : Cast is Wrong!\n");
        return nullptr;
    }
};
