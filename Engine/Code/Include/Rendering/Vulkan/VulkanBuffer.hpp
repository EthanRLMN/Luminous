#pragma once

#include "IBuffer.hpp"

#include "Struct/VulkanUtilities.hpp"


class VulkanBuffer final : public IBuffer
{
public:
    VulkanBuffer() = default;

    void Create(IDevice* a_device, ITexture* a_texture) override;
    void Destroy(IDevice* a_device) override;


    static void SetMeshBuffers(IDevice* a_device, ICommandPool* a_commandPool, IMesh* a_mesh);

    void CreateUniformBuffers(IDevice* a_device, ITexture* a_texture);

    VulkanBuffer* CastVulkan() override { return this; }

    [[nodiscard]] std::vector<VkBuffer> GetUniformBuffer() const { return m_uniformBuffer; }
    [[nodiscard]] std::vector<VkDeviceMemory> GetUniformBuffersMemory() const { return m_uniformBuffersMemory; }
    [[nodiscard]] std::vector<void*> GetUniformBuffersMapped() const { return m_uniformBuffersMapped; }


private:
    static void CopyBuffer(VkDevice a_device, VkQueue a_graphicsQueue, VkCommandPool a_commandPool, VkBuffer a_srcBuffer, VkBuffer a_dstBuffer, VkDeviceSize a_size);

    std::vector<VkBuffer> m_uniformBuffer { nullptr };
    std::vector<VkDeviceMemory> m_uniformBuffersMemory { nullptr };
    std::vector<void*> m_uniformBuffersMapped { nullptr };
};