#pragma once

#include "IMesh.hpp"
#include "Struct/VulkanUtilities.hpp"

class VulkanMesh final : public IMesh
{
public:
    bool Create(const IResourceParams& a_params) override;
    void Destroy(IDevice* a_device) override;
    VulkanMesh* CastVulkan() override { return this; }

    [[nodiscard]] VkBuffer& GetVertexBuffer()  { return m_vertexBuffer; }
    [[nodiscard]] VkDeviceMemory& GetVertexBufferMemory()  { return m_vertexBufferMemory; }
    [[nodiscard]] VkBuffer& GetIndexBuffer()  { return m_indexBuffer; }
    [[nodiscard]] VkDeviceMemory& GetIndexBufferMemory() { return m_indexBufferMemory; }


private:
    VkBuffer m_vertexBuffer{ nullptr };
    VkDeviceMemory m_vertexBufferMemory{ nullptr };
    VkBuffer m_indexBuffer{ nullptr };
    VkDeviceMemory m_indexBufferMemory{ nullptr };

};
