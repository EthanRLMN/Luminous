#pragma once

#include "IFrameBuffer.hpp"
#include "Logger.hpp"

class VulkanFrameBufferManager;
class ISwapChain;
class IDevice;

class IFrameBufferManager
{
public:
    virtual ~IFrameBufferManager() = default;

    virtual void Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass, IDepthResource* a_depthResource, IMultiSampling* a_multiSampling, const bool& a_isEditor) = 0;
    virtual void Destroy(IDevice* a_device) = 0;

    virtual VulkanFrameBufferManager* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan RenderPass : Cast is Wrong!\n");
        return nullptr;
    }

    virtual std::vector<IFrameBuffer*> GetFrameBuffers() const { return p_frameBuffers; }
    virtual IFrameBuffer* GetFrameBufferAt(const int& a_index) const { return p_frameBuffers[a_index]; }


protected:
    std::vector<IFrameBuffer*> p_frameBuffers;
};
