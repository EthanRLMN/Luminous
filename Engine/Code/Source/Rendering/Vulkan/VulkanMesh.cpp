#include <unordered_map>

#define TINYOBJLOADER_IMPLEMENTATION
#include "Rendering/Vulkan/VulkanMesh.hpp"
#include "ResourceManager/ResourceManager.hpp"

bool VulkanMesh::Create(IResourceManager* a_manager, IResourceParams a_params)
{
    a_manager->GetMeshLoader()->LoadModel(this, a_params.m_meshPath.c_str());
    return isLoaded;
}


void VulkanMesh::Destroy(...)
{
    
}
