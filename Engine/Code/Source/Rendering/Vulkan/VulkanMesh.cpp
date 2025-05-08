#include "Rendering/Vulkan/VulkanMesh.hpp"
#include "ResourceManager/ResourceManager.hpp"

#include "Rendering/Vulkan/VulkanDevice.hpp"

bool VulkanMesh::Create(const IResourceParams& a_params)
{
    AssimpModelLoader::LoadModel(this, a_params.m_meshPath.c_str());

    return IsLoaded();
}

void VulkanMesh::Destroy(IDevice* a_device)
{
    
    VkDevice l_device = a_device->CastVulkan()->GetDevice();
    
    vkDestroyBuffer(l_device, m_vertexBuffer, nullptr);
    vkDestroyBuffer(l_device, m_indexBuffer, nullptr);
    vkFreeMemory(l_device, m_vertexBufferMemory, nullptr);
    vkFreeMemory(l_device, m_indexBufferMemory, nullptr);
    
}
