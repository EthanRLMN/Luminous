#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "Matrix4.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

/**
 * @brief How many frames should be rendered ahead
 */
constexpr int MAX_FRAMES_IN_FLIGHT = 3;


struct SwapChainDetails
{
    VkSurfaceCapabilitiesKHR surfaceCapabilities { };
    std::vector<VkSurfaceFormatKHR> formats { };
    std::vector<VkPresentModeKHR> presentationModes { };
};


const std::vector deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };


struct Vertex
{
    Maths::Vector3 pos { Maths::Vector3::Zero };
    Maths::Vector2 texCoord = Maths::Vector2::One;
    Maths::Vector3 normal = Maths::Vector3::Zero;
    Maths::Vector3 color = Maths::Vector3(1.0, 1.0f, 1.0f);

    bool operator==(const Vertex& a_other) const noexcept { return pos == a_other.pos && texCoord == a_other.texCoord && color == a_other.color && normal == a_other.normal; }
};


struct VertexHasher
{
    size_t operator()(const Vertex& a_vertex) const
    {
        size_t hash = 0;

        hash ^= std::hash<float> { }(a_vertex.pos.x) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<float> { }(a_vertex.pos.y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<float> { }(a_vertex.pos.z) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

        hash ^= std::hash<float> { }(a_vertex.texCoord.x) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<float> { }(a_vertex.texCoord.y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

        hash ^= std::hash<float> { }(a_vertex.color.x) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<float> { }(a_vertex.color.y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<float> { }(a_vertex.color.z) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

        return hash;
    }
};


struct UniformBufferObject
{
    Maths::Matrix4 model { Maths::Matrix4::identity };
    Maths::Matrix4 view { Maths::Matrix4::identity };
    Maths::Matrix4 proj { Maths::Matrix4::identity };
	alignas(4) int debug;
};
