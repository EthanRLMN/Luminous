#pragma once

#include <string>
#include <vulkan/vulkan.h>

#include "ITexture.hpp"


class VulkanTexture final : public ITexture
{
public:
    bool Create(IResourceManager* a_manager, IResourceParams a_params) override;
    void Destroy(IDevice* a_device) override;
    VulkanTexture* CastVulkan() override { return this; };

    void CreateTextureImage(IDevice* a_device, ISwapChain* a_swapChain, ICommandPool* a_commandPool, const std::string& a_path);
    void CreateTextureImageView(IDevice* a_device);
    void CreateTextureSampler(IDevice* a_device);

    static void CreateBuffer(const VkDevice& a_device, const VkPhysicalDevice& a_physicalDevice, const VkDeviceSize& a_size, const VkBufferUsageFlags& a_usage, const VkMemoryPropertyFlags& a_properties, VkBuffer& a_buffer, VkDeviceMemory& a_bufferMemory, ISwapChain* a_swapChain);

    static void TransitionImageLayout(const VkDevice& a_device, const VkQueue& a_graphicsQueue, const VkCommandPool& a_commandPool, const VkImage& a_image, const VkFormat& a_format, const VkImageLayout& a_oldLayout, const VkImageLayout& a_newLayout);
    static VkCommandBuffer BeginSingleTimeCommands(const VkDevice& a_device, const VkCommandPool& a_commandPool);
    static void EndSingleTimeCommands(const VkDevice& a_device, const VkQueue& a_graphicsQueue, const VkCommandPool& a_commandPool, const VkCommandBuffer& a_commandBuffer);
    static void CopyBufferToImage(const VkDevice& a_device, const VkQueue& a_graphicsQueue, const VkCommandPool& a_commandPool, const VkBuffer& a_buffer, const VkImage& a_image, const uint32_t& a_width, const uint32_t& a_height);

    [[nodiscard]] VkImage GetTextureImage() const { return m_textureImage; }
    [[nodiscard]] VkDeviceMemory GetTextureImageMemory() const { return m_textureImageMemory; }
    [[nodiscard]] VkImageView GetTextureImageView() const { return m_textureImageView; }
    [[nodiscard]] VkSampler GetTextureSampler() const { return m_textureSampler; }


private:
    VkImage m_textureImage { nullptr };
    VkImageView m_textureImageView { nullptr };
    VkDeviceMemory m_textureImageMemory { nullptr };
    VkSampler m_textureSampler { nullptr };
};

