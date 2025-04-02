#pragma once

#include "IBuffer.hpp"

#include "Struct/VulkanUtilities.hpp"


class VulkanBuffer final : public IBuffer
{
public:
    VulkanBuffer() = default;

    void Create(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, IDepthResource* a_depthResource, IMesh* a_mesh) override;
    void Destroy(IDevice* a_device) override;

    void CreateVertexBuffers(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, IDepthResource* a_depthResource, IMesh* a_mesh);
    void CreateIndexBuffers(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, IDepthResource* a_depthResource, IMesh* a_mesh);
    void CreateUniformBuffers(IDevice* a_device, ITexture* a_texture, IDepthResource* a_depthResource);

    VulkanBuffer* CastVulkan() override { return this; }

    [[nodiscard]] VkBuffer GetVertexBuffer() const { return m_vertexBuffer; }
    [[nodiscard]] VkDeviceMemory GetVertexBufferMemory() const { return m_vertexBufferMemory; }
    [[nodiscard]] VkBuffer GetIndexBuffer() const { return m_indexBuffer; }
    [[nodiscard]] VkDeviceMemory GetIndexBufferMemory() const { return m_indexBufferMemory; }

    [[nodiscard]] std::vector<VkBuffer> GetUniformBuffer() const { return m_uniformBuffer; }
    [[nodiscard]] std::vector<VkDeviceMemory> GetUniformBuffersMemory() const { return m_uniformBuffersMemory; }
    [[nodiscard]] std::vector<void*> GetUniformBuffersMapped() const { return m_uniformBuffersMapped; }


private:
    void CopyBuffer(VkDevice a_device, VkQueue a_graphicsQueue, VkCommandPool a_commandPool, VkBuffer a_srcBuffer, VkBuffer a_dstBuffer, VkDeviceSize a_size, ITexture* a_texture);

    VkBuffer m_vertexBuffer { nullptr };
    VkDeviceMemory m_vertexBufferMemory { nullptr };
    VkBuffer m_indexBuffer { nullptr };
    VkDeviceMemory m_indexBufferMemory { nullptr };

    std::vector<VkBuffer> m_uniformBuffer { nullptr };
    std::vector<VkDeviceMemory> m_uniformBuffersMemory { nullptr };
    std::vector<void*> m_uniformBuffersMapped { nullptr };
};
