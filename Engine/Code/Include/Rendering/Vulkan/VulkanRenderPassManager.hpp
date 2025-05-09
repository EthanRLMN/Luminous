#pragma once

#include "IRenderPassManager.hpp"

class VulkanRenderPassManager final : public IRenderPassManager
{
public:
    void Create(ISwapChain* a_swapChain, IDevice* a_device, const bool& a_isEditor) override;
    void Destroy(IDevice* a_device) override;

    VulkanRenderPassManager* CastVulkan() override { return this; };
    VulkanRenderPass* GetRenderPass() const { return m_renderPass; }

private:
    VulkanRenderPass* m_renderPass{ nullptr };
};