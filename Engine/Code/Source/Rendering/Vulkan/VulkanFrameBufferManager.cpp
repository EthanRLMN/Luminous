#include "Rendering/Vulkan/VulkanFrameBufferManager.hpp"

#include "Rendering/Vulkan/VulkanFrameBuffer.hpp"

void VulkanFrameBufferManager::Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass, IDepthResource* a_depthResource, IMultiSampling* a_multiSampling, const bool& a_isEditor)
{
    m_frameBuffer = new VulkanFrameBuffer();
    m_frameBuffer->Create(a_device, a_swapChain, a_renderPass, a_depthResource, a_multiSampling, a_isEditor);

    p_frameBuffers.push_back(m_frameBuffer);
}

void VulkanFrameBufferManager::Destroy(IDevice* a_device)
{
    for (IFrameBuffer* l_frameBuffer : p_frameBuffers)
    {
        l_frameBuffer->Destroy(a_device);
        delete l_frameBuffer;
    }
    p_frameBuffers.clear();
    m_frameBuffer = nullptr;
}
