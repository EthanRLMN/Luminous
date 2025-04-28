#include "Rendering/Vulkan/VulkanMesh.hpp"
#include "ResourceManager/ResourceManager.hpp"

bool VulkanMesh::Create(IResourceManager* a_manager, const IResourceParams& a_params)
{
    AssimpModelLoader::LoadModel(this, a_params.m_meshPath.c_str());

    return IsLoaded();
}