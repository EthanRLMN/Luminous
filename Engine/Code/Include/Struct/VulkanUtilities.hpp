#pragma once
#include <Matrix4.hpp>
#include <Vector3.hpp>
#include <vector>

#include "Rendering/API/Vulkan/VulkanSurface.hpp"

constexpr int MAX_FRAMES_IN_FLIGHT = 3;

struct SwapChainDetails
{
    VkSurfaceCapabilitiesKHR surfaceCapabilities{};
    std::vector<VkSurfaceFormatKHR> formats{};
    std::vector<VkPresentModeKHR> presentationModes{};
};

struct MainDevice
{
    VkPhysicalDevice physicalDevice{};
    VkDevice logicalDevice{};
};

const std::vector deviceExtensions =
    {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct QueueFamilyIndices
{
    int graphicsFamily = -1;
    int presentationFamily = -1;

    bool isValid() const
    {
        return graphicsFamily >= 0 && presentationFamily >= 0;
    }
};

struct Vertex
{
    Maths::Vector3 pos = Maths::Vector3::Zero;
    Maths::Vector3 color = Maths::Vector3::One;
    Maths::Vector3 texCoord = Maths::Vector3::Zero;

    bool operator==(const Vertex& other) const noexcept
    {
        return pos == other.pos && texCoord == other.texCoord && color == other.color;
    }
};

struct VertexHasher
{
    size_t operator()(const Vertex& vertex) const
    {
        size_t hash = 0;

        hash ^= std::hash<float>{}(vertex.pos.x) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<float>{}(vertex.pos.y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<float>{}(vertex.pos.z) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

        hash ^= std::hash<float>{}(vertex.texCoord.x) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<float>{}(vertex.texCoord.y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

        hash ^= std::hash<float>{}(vertex.color.x) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<float>{}(vertex.color.y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<float>{}(vertex.color.z) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

        return hash;
    }
};

struct UniformBufferObject
{
    alignas(16) Maths::Matrix4 model = Maths::Matrix4::identity;
    alignas(16) Maths::Matrix4 view = Maths::Matrix4::identity;
    alignas(16) Maths::Matrix4 projection = Maths::Matrix4::identity;
};





