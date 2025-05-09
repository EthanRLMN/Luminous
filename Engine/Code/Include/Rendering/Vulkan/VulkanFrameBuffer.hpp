#pragma once

#include <vulkan/vulkan.h>

#include "IFrameBuffer.hpp"


class VulkanFrameBuffer final : public IFrameBuffer
{
public:
    void Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass, IDepthResource* a_depthResource, IMultiSampling* a_multiSampling, const bool& a_isEditor) override;
    void Destroy(IDevice* a_device) override;
    VulkanFrameBuffer* CastVulkan() override { return this; }

    [[nodiscard]] std::vector<VkFramebuffer> GetFrameBuffers() const { return m_frameBuffers; }

    void SetFrameBuffersSize(const size_t& a_size) { m_frameBuffers.resize(a_size); }

private:
    std::vector<VkFramebuffer> m_frameBuffers{ nullptr };
};