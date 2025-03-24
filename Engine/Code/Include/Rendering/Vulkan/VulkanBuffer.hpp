#pragma once

#include <vulkan/vulkan.hpp>

#include "IBuffer.hpp"

#include "Rendering/Vulkan/VulkanCommandPool.hpp"

#include "Struct/VulkanUtilities.hpp"

class VulkanBuffer final : public IBuffer
{
public:
    VulkanBuffer() = default;
    void Destroy() override {};

    void Create(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, IDepthResource* a_depthResource, IModel* a_model) override;

    void CreateVertexBuffers(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, IDepthResource* a_depthResource, IModel* a_model);
    void CreateIndexBuffers(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, IDepthResource* a_depthResource, IModel* a_model);
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

    VkBuffer m_vertexBuffer{VK_NULL_HANDLE};
    VkDeviceMemory m_vertexBufferMemory{VK_NULL_HANDLE};
    VkBuffer m_indexBuffer{VK_NULL_HANDLE};
    VkDeviceMemory m_indexBufferMemory{VK_NULL_HANDLE};

    std::vector<VkBuffer> m_uniformBuffer{VK_NULL_HANDLE};
    std::vector<VkDeviceMemory> m_uniformBuffersMemory{VK_NULL_HANDLE};
    std::vector<void*> m_uniformBuffersMapped{VK_NULL_HANDLE};
};
