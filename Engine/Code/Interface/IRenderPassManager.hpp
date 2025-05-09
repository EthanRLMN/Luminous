#pragma once

#include "IRenderPass.hpp"
#include "Logger.hpp"

class VulkanRenderPassManager;
class ISwapChain;
class IDevice;

class IRenderPassManager
{
public:
    virtual ~IRenderPassManager() = default;

    virtual void Create(ISwapChain* a_swapChain, IDevice* a_device, const bool& a_isEditor) = 0;
    virtual void Destroy(IDevice* a_device) = 0;

    virtual VulkanRenderPassManager* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan RenderPass : Cast is Wrong!\n");
        return nullptr;
    }

    [[nodiscard]] virtual std::vector<IRenderPass*> GetRenderPasses() const { return p_renderPasses; }
    [[nodiscard]] virtual IRenderPass* GetRenderPassAt(const int& a_index) const { return p_renderPasses[a_index]; }

protected:
    std::vector<IRenderPass*> p_renderPasses;
};
