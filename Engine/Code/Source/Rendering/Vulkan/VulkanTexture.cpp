#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "ICommandPool.hpp"
#include "IDepthResource.hpp"
#include "IDevice.hpp"
#include "ISwapChain.hpp"

#include "Rendering/Vulkan/VulkanTexture.hpp"

#include "IDescriptorSetLayout.hpp"
#include "Rendering/Vulkan/VulkanCommandPool.hpp"
#include "Rendering/Vulkan/VulkanDescriptorSetLayout.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"


bool VulkanTexture::Create(const IResourceParams& a_params)
{
    IDevice* l_device = a_params.m_device;
    ICommandPool* l_commandPool = a_params.m_commandPool;
    IDescriptorSetLayout* l_descriptorSetLayout = a_params.m_descriptorSetLayout;

    if (l_device == nullptr)
        DEBUG_LOG_ERROR("DEVICE IS NULL");

    CreateTextureImage(l_device, l_commandPool, a_params.m_texturePath);
    CreateTextureImageView(l_device);
    CreateTextureSampler(l_device);
    DEBUG_LOG_INFO("Vulkan Texture : Texture Created!\n");

    CreateDescriptorPool(l_device);
    CreateDescriptorSets(l_device, l_descriptorSetLayout);

    return true;
}


void VulkanTexture::Destroy(IDevice* a_device)
{
    const VkDevice l_vkdevice = a_device->CastVulkan()->GetDevice();
    vkDeviceWaitIdle(l_vkdevice);

    if (m_textureImageView != VK_NULL_HANDLE)
    {
        vkDestroyImageView(l_vkdevice, m_textureImageView, nullptr);
        m_textureImageView = VK_NULL_HANDLE;
    }

    if (m_textureImage != VK_NULL_HANDLE)
    {
        vkDestroyImage(l_vkdevice, m_textureImage, nullptr);
        m_textureImage = VK_NULL_HANDLE;
    }

    if (m_textureSampler != VK_NULL_HANDLE)
    {
        vkDestroySampler(l_vkdevice, m_textureSampler, nullptr);
        m_textureSampler = VK_NULL_HANDLE;
    }

    if (m_textureImageMemory != VK_NULL_HANDLE)
    {
        vkFreeMemory(l_vkdevice, m_textureImageMemory, nullptr);
        m_textureImageMemory = VK_NULL_HANDLE;
    }

    DEBUG_LOG_INFO("Vulkan Texture : Texture Destroy!\n");
}


// TODO: Cleanup
void VulkanTexture::CreateTextureImage(IDevice* a_device, ICommandPool* a_commandPool, const std::string& a_path)
{
    if (a_device == nullptr)
    {
        DEBUG_LOG_ERROR("DEVICE IS NULL");
        return;
    }

    const VkDevice l_vkDevice = a_device->CastVulkan()->GetDevice();
    const VkPhysicalDevice l_vkPhysicalDevice = a_device->CastVulkan()->GetPhysicalDevice();
    const VkQueue l_vkGraphicsQueue = a_device->CastVulkan()->GetGraphicsQueue();
    const VkCommandPool l_vkCommandPool = a_commandPool->CastVulkan()->GetCommandPool();

    int l_texWidth, l_texHeight, l_texChannels = -1;
    stbi_uc* l_pixels = stbi_load(a_path.c_str(), &l_texWidth, &l_texHeight, &l_texChannels, STBI_rgb_alpha);
    const VkDeviceSize l_imageSize = l_texWidth * l_texHeight * 4;
    m_mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(l_texWidth, l_texHeight)))) + 1;

    if (!l_pixels)
        DEBUG_LOG_ERROR("Vulkan Texture : Failed to load Texture Image!\n");

    VkBuffer l_stagingBuffer = nullptr;
    VkDeviceMemory l_stagingBufferMemory = nullptr;
    CreateBuffer(l_vkDevice, l_vkPhysicalDevice, l_imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, l_stagingBuffer, l_stagingBufferMemory);

    void* l_data = nullptr;
    vkMapMemory(l_vkDevice, l_stagingBufferMemory, 0, l_imageSize, 0, &l_data);
    memcpy(l_data, l_pixels, l_imageSize);
    vkUnmapMemory(l_vkDevice, l_stagingBufferMemory);
    stbi_image_free(l_pixels);

    VulkanSwapChain::CreateImage(l_vkDevice, l_vkPhysicalDevice, l_texWidth, l_texHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_textureImage, m_textureImageMemory, VK_SAMPLE_COUNT_1_BIT, m_mipLevels);

    TransitionImageLayout(l_vkDevice, l_vkGraphicsQueue, l_vkCommandPool, m_textureImage, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, m_mipLevels);
    CopyBufferToImage(l_vkDevice, l_vkGraphicsQueue, l_vkCommandPool, l_stagingBuffer, m_textureImage, static_cast<uint32_t>(l_texWidth), static_cast<uint32_t>(l_texHeight));

    vkDestroyBuffer(l_vkDevice, l_stagingBuffer, nullptr);
    vkFreeMemory(l_vkDevice, l_stagingBufferMemory, nullptr);
    GenerateMipMaps(a_device, l_vkGraphicsQueue, a_commandPool->CastVulkan()->GetCommandPool(), m_textureImage, VK_FORMAT_R8G8B8A8_SRGB, l_texWidth, l_texHeight);
}


void VulkanTexture::CreateTextureImageView(IDevice* a_device)
{
    m_textureImageView = VulkanSwapChain::CreateImageView(m_textureImage, a_device->CastVulkan()->GetDevice(), VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, m_mipLevels);
}


void VulkanTexture::CreateTextureSampler(IDevice* a_device)
{
    VkPhysicalDeviceProperties l_properties{};
    vkGetPhysicalDeviceProperties(a_device->CastVulkan()->GetPhysicalDevice(), &l_properties);

    VkSamplerCreateInfo l_samplerInfo{ };
    l_samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    l_samplerInfo.magFilter = VK_FILTER_LINEAR;
    l_samplerInfo.minFilter = VK_FILTER_LINEAR;
    l_samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    l_samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    l_samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    l_samplerInfo.anisotropyEnable = VK_TRUE;
    l_samplerInfo.maxAnisotropy = l_properties.limits.maxSamplerAnisotropy;
    l_samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    l_samplerInfo.unnormalizedCoordinates = VK_FALSE;
    l_samplerInfo.compareEnable = VK_FALSE;
    l_samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    l_samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    l_samplerInfo.minLod = 0.0f;
    l_samplerInfo.maxLod = static_cast<float>(m_mipLevels);
    l_samplerInfo.mipLodBias = 0.0f;
    l_samplerInfo.pNext = nullptr;

    if (vkCreateSampler(a_device->CastVulkan()->GetDevice(), &l_samplerInfo, nullptr, &m_textureSampler) != VK_SUCCESS)
        DEBUG_LOG_ERROR("Vulkan Texture : Failed to create Texture Sampler!\n");
}


void VulkanTexture::CreateDescriptorPool(IDevice* a_device)
{
    std::array<VkDescriptorPoolSize, 1> l_poolSizes{ };
    l_poolSizes[0].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    l_poolSizes[0].descriptorCount = 1;

    VkDescriptorPoolCreateInfo l_poolInfo{ };
    l_poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    l_poolInfo.poolSizeCount = static_cast<uint32_t>(l_poolSizes.size());
    l_poolInfo.pPoolSizes = l_poolSizes.data();
    l_poolInfo.maxSets = 1;
    l_poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    l_poolInfo.pNext = nullptr;

    if (vkCreateDescriptorPool(a_device->CastVulkan()->GetDevice(), &l_poolInfo, nullptr, &m_textureDescriptorPool) != VK_SUCCESS)
        DEBUG_LOG_ERROR("Failed to create descriptor pool\n");

    DEBUG_LOG_INFO("Vulkan Descriptors : DescriptorPool created!\n");
}

void VulkanTexture::CreateDescriptorSets(IDevice* a_device, IDescriptorSetLayout* a_layout)
{

    const std::vector<VkDescriptorSetLayout> l_layouts(1, a_layout->CastVulkan()->GetTextureDescriptorSetLayout());

    VkDescriptorSetAllocateInfo l_allocateInfo{ };
    l_allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    l_allocateInfo.descriptorPool = m_textureDescriptorPool;
    l_allocateInfo.descriptorSetCount = 1;
    l_allocateInfo.pSetLayouts = l_layouts.data();
    l_allocateInfo.pNext = nullptr;

    if (vkAllocateDescriptorSets(a_device->CastVulkan()->GetDevice(), &l_allocateInfo, &m_textureDescriptorSets) != VK_SUCCESS)
        DEBUG_LOG_ERROR("failed to allocate descriptor sets !\n");

    UpdateDescriptorSets(a_device);
}

void VulkanTexture::UpdateDescriptorSets(IDevice* a_device) const
{
    VkDescriptorImageInfo l_imageInfo{};
    l_imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    l_imageInfo.imageView = GetTextureImageView();
    l_imageInfo.sampler = GetTextureSampler();

    std::array<VkWriteDescriptorSet, 1> l_descriptorWrites{ };
    l_descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    l_descriptorWrites[0].dstSet = m_textureDescriptorSets;
    l_descriptorWrites[0].dstBinding = 0;
    l_descriptorWrites[0].dstArrayElement = 0;
    l_descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    l_descriptorWrites[0].descriptorCount = 1;
    l_descriptorWrites[0].pImageInfo = &l_imageInfo;
    l_descriptorWrites[0].pNext = nullptr;

    vkUpdateDescriptorSets(a_device->CastVulkan()->GetDevice(), static_cast<uint32_t>(l_descriptorWrites.size()), l_descriptorWrites.data(), 0, nullptr);
}


void VulkanTexture::CreateBuffer(const VkDevice& a_device, const VkPhysicalDevice& a_physicalDevice, const VkDeviceSize& a_size, const VkBufferUsageFlags& a_usage, const VkMemoryPropertyFlags& a_properties, VkBuffer& a_buffer, VkDeviceMemory& a_bufferMemory)
{
    VkBufferCreateInfo l_bufferInfo{ };
    l_bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    l_bufferInfo.size = a_size;
    l_bufferInfo.usage = a_usage;
    l_bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    l_bufferInfo.pNext = nullptr;

    if (vkCreateBuffer(a_device, &l_bufferInfo, nullptr, &a_buffer) != VK_SUCCESS)
        DEBUG_LOG_ERROR("Vulkan Texture : Failed to load buffer!\n");

    VkMemoryRequirements l_memoryRequirements{};
    vkGetBufferMemoryRequirements(a_device, a_buffer, &l_memoryRequirements);

    VkMemoryAllocateInfo l_allocateInfo{ };
    l_allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    l_allocateInfo.allocationSize = l_memoryRequirements.size;
    l_allocateInfo.memoryTypeIndex = VulkanSwapChain::FindMemoryType(a_physicalDevice, l_memoryRequirements.memoryTypeBits, a_properties);
    l_allocateInfo.pNext = nullptr;

    if (vkAllocateMemory(a_device, &l_allocateInfo, nullptr, &a_bufferMemory) != VK_SUCCESS)
        DEBUG_LOG_ERROR("Vulkan Texture : Failed to allocate Buffer Memory!\n");

    vkBindBufferMemory(a_device, a_buffer, a_bufferMemory, 0);
}


void VulkanTexture::TransitionImageLayout(const VkDevice& a_device, const VkQueue& a_graphicsQueue, const VkCommandPool& a_commandPool, const VkImage& a_image, const VkImageLayout& a_oldLayout, const VkImageLayout& a_newLayout, const uint32_t& a_mipLevels)
{
    const VkCommandBuffer l_commandBuffer = BeginSingleTimeCommands(a_device, a_commandPool);
    VkImageMemoryBarrier l_barrier{ };
    l_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    l_barrier.oldLayout = a_oldLayout;
    l_barrier.newLayout = a_newLayout;
    l_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    l_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    l_barrier.image = a_image;
    l_barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    l_barrier.subresourceRange.baseMipLevel = 0;
    l_barrier.subresourceRange.levelCount = a_mipLevels;
    l_barrier.subresourceRange.baseArrayLayer = 0;
    l_barrier.subresourceRange.layerCount = 1;
    l_barrier.pNext = nullptr;

    VkPipelineStageFlags l_sourceStage{};
    VkPipelineStageFlags l_destinationStage{};
    if (a_oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && a_newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
    {
        l_barrier.srcAccessMask = 0;
        l_barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        l_sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        l_destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    } else if (a_oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && a_newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
    {
        l_barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        l_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        l_sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        l_destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    } else
        throw std::invalid_argument("Unsupported layout transition");

    vkCmdPipelineBarrier(l_commandBuffer, l_sourceStage, l_destinationStage, 0, 0, nullptr, 0, nullptr, 1, &l_barrier);
    EndSingleTimeCommands(a_device, a_graphicsQueue, a_commandPool, l_commandBuffer);
}


VkCommandBuffer VulkanTexture::BeginSingleTimeCommands(const VkDevice& a_device, const VkCommandPool& a_commandPool)
{
    VkCommandBufferAllocateInfo l_allocateInfo{ };
    l_allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    l_allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    l_allocateInfo.commandPool = a_commandPool;
    l_allocateInfo.commandBufferCount = 1;
    l_allocateInfo.pNext = nullptr;

    VkCommandBuffer l_commandBuffer{};
    if (a_commandPool == nullptr)
    {
        DEBUG_LOG_ERROR("Vulkan Texture : Invalid Command Pool!\n");
        return nullptr;
    }

    if (const VkResult result = vkAllocateCommandBuffers(a_device, &l_allocateInfo, &l_commandBuffer); result != VK_SUCCESS)
    {
        DEBUG_LOG_ERROR("Vulkan Texture : Error with vkAllocateCommandBuffers!\n");
        return nullptr;
    }

    VkCommandBufferBeginInfo l_beginInfo{ };
    l_beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    l_beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    l_beginInfo.pNext = nullptr;

    vkBeginCommandBuffer(l_commandBuffer, &l_beginInfo);
    return l_commandBuffer;
}


void VulkanTexture::EndSingleTimeCommands(const VkDevice& a_device, const VkQueue& a_graphicsQueue, const VkCommandPool& a_commandPool, const VkCommandBuffer& a_commandBuffer)
{
    vkEndCommandBuffer(a_commandBuffer);

    VkSubmitInfo l_submitInfo{ };
    l_submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    l_submitInfo.commandBufferCount = 1;
    l_submitInfo.pCommandBuffers = &a_commandBuffer;
    l_submitInfo.pNext = nullptr;

    vkQueueSubmit(a_graphicsQueue, 1, &l_submitInfo, nullptr);
    vkQueueWaitIdle(a_graphicsQueue);
    vkFreeCommandBuffers(a_device, a_commandPool, 1, &a_commandBuffer);
}


void VulkanTexture::CopyBufferToImage(const VkDevice& a_device, const VkQueue& a_graphicsQueue, const VkCommandPool& a_commandPool, const VkBuffer& a_buffer, const VkImage& a_image, const uint32_t& a_width, const uint32_t& a_height)
{
    const VkCommandBuffer l_commandBuffer = BeginSingleTimeCommands(a_device, a_commandPool);
    VkBufferImageCopy l_bufferImageCopy{};
    l_bufferImageCopy.bufferOffset = 0;
    l_bufferImageCopy.bufferRowLength = 0;
    l_bufferImageCopy.bufferImageHeight = 0;
    l_bufferImageCopy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    l_bufferImageCopy.imageSubresource.mipLevel = 0;
    l_bufferImageCopy.imageSubresource.baseArrayLayer = 0;
    l_bufferImageCopy.imageSubresource.layerCount = 1;
    l_bufferImageCopy.imageOffset = { 0, 0, 0 };
    l_bufferImageCopy.imageExtent = { a_width, a_height, 1 };

    vkCmdCopyBufferToImage(l_commandBuffer, a_buffer, a_image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &l_bufferImageCopy);
    EndSingleTimeCommands(a_device, a_graphicsQueue, a_commandPool, l_commandBuffer);
}

// TODO: Cleanup
void VulkanTexture::GenerateMipMaps(IDevice* a_device, const VkQueue& a_graphicsQueue, const VkCommandPool& a_commandPool, const VkImage& a_image, const VkFormat& a_imageFormat, const uint32_t& a_width, const uint32_t& a_height) const
{
    VkFormatProperties l_formatProperties{};
    vkGetPhysicalDeviceFormatProperties(a_device->CastVulkan()->GetPhysicalDevice(), a_imageFormat, &l_formatProperties);

    if (!(l_formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT))
        throw std::runtime_error("texture image format does not support linear blitting!");

    const VkCommandBuffer l_commandBuffer = BeginSingleTimeCommands(a_device->CastVulkan()->GetDevice(), a_commandPool);
    VkImageMemoryBarrier l_barrier{ };
    l_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    l_barrier.image = a_image;
    l_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    l_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    l_barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    l_barrier.subresourceRange.baseArrayLayer = 0;
    l_barrier.subresourceRange.layerCount = 1;
    l_barrier.subresourceRange.levelCount = 1;
    l_barrier.pNext = nullptr;

    int32_t l_mipWidth = static_cast<int32_t>(a_width);
    int32_t l_mipHeight = static_cast<int32_t>(a_height);
    for (uint32_t i = 1; i < m_mipLevels; ++i)
    {
        l_barrier.subresourceRange.baseMipLevel = i - 1;
        l_barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        l_barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        l_barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        l_barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        vkCmdPipelineBarrier(l_commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &l_barrier);

        VkImageBlit l_blit{};
        l_blit.srcOffsets[0] = { 0, 0, 0 };
        l_blit.srcOffsets[1] = { l_mipWidth, l_mipHeight, 1 };
        l_blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        l_blit.srcSubresource.mipLevel = i - 1;
        l_blit.srcSubresource.baseArrayLayer = 0;
        l_blit.srcSubresource.layerCount = 1;
        l_blit.dstOffsets[0] = { 0, 0, 0 };
        l_blit.dstOffsets[1] = { l_mipWidth > 1 ? l_mipWidth / 2 : 1, l_mipHeight > 1 ? l_mipHeight / 2 : 1, 1 };
        l_blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        l_blit.dstSubresource.mipLevel = i;
        l_blit.dstSubresource.baseArrayLayer = 0;
        l_blit.dstSubresource.layerCount = 1;
        vkCmdBlitImage(l_commandBuffer, a_image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, a_image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &l_blit, VK_FILTER_LINEAR);

        l_barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        l_barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        l_barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        l_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        vkCmdPipelineBarrier(l_commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1, &l_barrier);

        if (l_mipWidth > 1)
            l_mipWidth /= 2;
        if (l_mipHeight > 1)
            l_mipHeight /= 2;
    }

    l_barrier.subresourceRange.baseMipLevel = m_mipLevels - 1;
    l_barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    l_barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    l_barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    l_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    vkCmdPipelineBarrier(l_commandBuffer,
                         VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
                         0, nullptr,
                         0, nullptr,
                         1, &l_barrier);

    EndSingleTimeCommands(a_device->CastVulkan()->GetDevice(), a_graphicsQueue, a_commandPool, l_commandBuffer);
}
