#pragma once

#include "ICommandBuffer.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"

class VulkanCommandBuffer final : public ICommandBuffer
{
public:
    void Create(IDevice* a_device, ICommandPool* a_commandPool) override;
    void Destroy() override {};
    VulkanCommandBuffer* CastVulkan() override { return this; }

    [[nodiscard]] std::vector<VkCommandBuffer>& GetCommandBuffers() { return m_commandBuffers; }


private:
    std::vector<VkCommandBuffer> m_commandBuffers{ nullptr };
};
