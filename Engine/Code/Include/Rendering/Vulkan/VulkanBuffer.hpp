#pragma once

#include "IBuffer.hpp"

#include "Struct/VulkanUtilities.hpp"


class VulkanBuffer final : public IBuffer
{
public:
    VulkanBuffer() = default;

    void Create(IDevice* a_device, ICommandPool* a_commandPool, const std::vector<IMesh*>& a_meshes) override;
    void Destroy(IDevice* a_device) override;

    void CreateVertexBuffers(IDevice* a_device, ICommandPool* a_commandPool, const std::vector<IMesh*>& a_meshes);
    void CreateIndexBuffers(IDevice* a_device, ICommandPool* a_commandPool, const std::vector<IMesh*>& a_meshes);
    void CreateUniformBuffers(IDevice* a_device);

    VulkanBuffer* CastVulkan() override { return this; }

    [[nodiscard]] VkBuffer GetVertexBuffer() const { return m_vertexBuffer; }
    [[nodiscard]] VkDeviceMemory GetVertexBufferMemory() const { return m_vertexBufferMemory; }
    [[nodiscard]] VkBuffer GetIndexBuffer() const { return m_indexBuffer; }
    [[nodiscard]] VkDeviceMemory GetIndexBufferMemory() const { return m_indexBufferMemory; }


    [[nodiscard]] std::vector <VkBuffer> GetVertexBuffers() const { return m_vertexBuffers; }
    [[nodiscard]] std::vector <VkDeviceMemory> GetVertexBuffersMemory() const { return m_vertexBuffersMemory; }
    [[nodiscard]] std::vector <VkBuffer> GetIndexBuffers() const { return m_indexBuffers; }
    [[nodiscard]] std::vector <VkDeviceMemory> GetIndexBuffersMemory() const { return m_indexBuffersMemory; }


    [[nodiscard]] std::vector<VkBuffer> GetUniformBuffer() const { return m_uniformBuffer; }
    [[nodiscard]] std::vector<VkDeviceMemory> GetUniformBuffersMemory() const { return m_uniformBuffersMemory; }
    [[nodiscard]] std::vector<void*> GetUniformBuffersMapped() const { return m_uniformBuffersMapped; }

    [[nodiscard]] std::vector<VkBuffer> GetLightUniformBuffer() const { return m_lightUniformBuffer; }
    [[nodiscard]] std::vector<VkDeviceMemory> GetLightUniformBuffersMemory() const { return m_lightUniformBuffersMemory; }
    [[nodiscard]] std::vector<void*> GetLightUniformBuffersMapped() const { return m_lightUniformBuffersMapped; }


private:
    static void CopyBuffer(const VkDevice& a_device, const VkQueue& a_graphicsQueue, const VkCommandPool& a_commandPool, const VkBuffer& a_srcBuffer, const VkBuffer& a_dstBuffer, VkDeviceSize a_size);

    VkBuffer m_vertexBuffer { nullptr };
    VkDeviceMemory m_vertexBufferMemory { nullptr };
    VkBuffer m_indexBuffer { nullptr };
    VkDeviceMemory m_indexBufferMemory { nullptr };

    std::vector<VkBuffer> m_vertexBuffers{ nullptr };
    std::vector<VkDeviceMemory> m_vertexBuffersMemory{ nullptr };
    std::vector<VkBuffer> m_indexBuffers{ nullptr };
    std::vector<VkDeviceMemory> m_indexBuffersMemory{ nullptr };

    std::vector<VkBuffer> m_uniformBuffer { nullptr };
    std::vector<VkDeviceMemory> m_uniformBuffersMemory { nullptr };
    std::vector<void*> m_uniformBuffersMapped { nullptr };

    std::vector<VkBuffer> m_lightUniformBuffer{ nullptr };
    std::vector<VkDeviceMemory> m_lightUniformBuffersMemory{ nullptr };
    std::vector<void*> m_lightUniformBuffersMapped{ nullptr };

};