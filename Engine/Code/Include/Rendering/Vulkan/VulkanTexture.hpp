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

    void CreateTextureImage(IDevice* a_device, ISwapChain* a_swapChain, IDepthResource* a_depthResource, ICommandPool* a_commandPool, const std::string& a_path);
    void CreateTextureImageView(IDevice* a_device, ISwapChain* a_swapChain);
    void CreateTextureSampler(IDevice* a_device);

    void CreateBuffer(const VkDevice& a_device, const VkPhysicalDevice& a_physicalDevice, const VkDeviceSize& a_size, const VkBufferUsageFlags& a_usage, const VkMemoryPropertyFlags& a_properties, VkBuffer& a_buffer, VkDeviceMemory& a_bufferMemory, ISwapChain* a_swapChain);

    void TransitionImageLayout(const VkDevice& a_device, const VkQueue& a_graphicsQueue, const VkCommandPool& a_commandPool, const VkImage& a_image, const VkFormat& a_format, const VkImageLayout& a_oldLayout, const VkImageLayout& a_newLayout);
    VkCommandBuffer BeginSingleTimeCommands(const VkDevice& a_device, const VkCommandPool& a_commandPool);
    void EndSingleTimeCommands(const VkDevice& a_device, const VkQueue& a_graphicsQueue, const VkCommandPool& a_commandPool, const VkCommandBuffer& a_commandBuffer);
    void CopyBufferToImage(const VkDevice& a_device, const VkQueue& a_graphicsQueue, const VkCommandPool& a_commandPool, const VkBuffer& a_buffer, const VkImage& a_image, const uint32_t& a_width, const uint32_t& a_height);

    [[nodiscard]] VkImage GetTextureImage() const;
    [[nodiscard]] VkDeviceMemory GetTextureImageMemory() const;
    [[nodiscard]] VkImageView GetTextureImageView() const;
    [[nodiscard]] VkSampler GetTextureSampler() const;


private:
    VkImage m_textureImage { nullptr };
    VkImageView m_textureImageView { nullptr };
    VkDeviceMemory m_textureImageMemory { nullptr };
    VkSampler m_textureSampler { nullptr };
};

