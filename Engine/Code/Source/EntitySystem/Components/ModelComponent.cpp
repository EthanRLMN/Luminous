#include "EntitySystem/Components/ModelComponent.hpp"
#include "ResourceManager/ResourceManager.hpp"


void ModelComponent::Initialize() 
{
    
    SetMesh("Engine/Assets/Models/viking_room.obj");
    SetTexture("Engine/Assets/Textures/viking_room.png");
}

void ModelComponent::SetMesh(std::string a_path) 
{
    
    IResourceParams l_meshParams{};
    l_meshParams.m_meshPath = a_path;
    m_mesh = ResourceManager::GetInstance().LoadResource<VulkanMesh>(l_meshParams);
}

void ModelComponent::SetTexture(std::string a_path)
{ 
    IResourceParams l_texParams{  };
    l_texParams.m_texturePath = a_path;
    m_texture = ResourceManager::GetInstance().LoadResource<VulkanTexture>(l_texParams);
}
