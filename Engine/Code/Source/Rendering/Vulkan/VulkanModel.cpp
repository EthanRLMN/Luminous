#include <unordered_map>

#define TINYOBJLOADER_IMPLEMENTATION
#include "Rendering/Vulkan/VulkanModel.hpp"
#include "ResourceManager/ResourceManager.hpp"

bool VulkanMesh::Create(IResourceManager* a_manager, std::string a_file)
{
    a_manager->GetMeshLoader()->LoadModel(this, a_file.c_str());
    return isLoaded;
}


void VulkanMesh::Destroy()
{
    
}
