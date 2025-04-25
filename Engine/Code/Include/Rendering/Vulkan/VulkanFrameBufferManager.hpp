#pragma once
#include "IFrameBufferManager.hpp"


class VulkanFrameBufferManager final : public IFrameBufferManager
{
public:
    void Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass, IDepthResource* a_depthResource, IMultiSampling* a_multiSampling, const bool& a_isEditor) override;
    void Destroy(IDevice* a_device) override;
    VulkanFrameBufferManager* CastVulkan() override { return this; };
};