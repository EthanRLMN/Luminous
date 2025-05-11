#include "Game/Systems/Component/ModelComponent.hpp"
#include "Engine.hpp"
#include "Rendering/Vulkan/VulkanBuffer.hpp"
#include "ResourceManager/ResourceManager.hpp"


void ModelComponent::Initialize()
{
    SetMesh("Engine/Assets/Default/Models/CCP2.fbx"); // Default mesh
    SetTexture("Engine/Assets/Default/Textures/CCP2_albedo.png"); // Default Texture

    if (m_shouldLoadResources)
    {
        if (!m_pendingMeshPath.empty())
            SetMesh(m_pendingMeshPath);
        if (!m_pendingTexturePath.empty())
            SetTexture(m_pendingTexturePath);

        m_shouldLoadResources = false;
    }
}


void ModelComponent::SetMesh(const std::string& a_path)
{
    IResourceParams l_meshParams { GetEngine()->GetDevice(), GetEngine()->GetSwapChain(), GetEngine()->GetDepthResource(), GetEngine()->GetCommandPool(), GetEngine()->GetDescriptionSetLayout() };
    l_meshParams.m_meshPath = a_path;
    m_mesh = ResourceManager::GetInstance().LoadResource<VulkanMesh>(l_meshParams);
    VulkanBuffer::SetMeshBuffers(GetEngine()->GetDevice(), GetEngine()->GetCommandPool(), m_mesh);
}


void ModelComponent::SetTexture(const std::string& a_path)
{ 
    IResourceParams l_texParams { GetEngine()->GetDevice(), GetEngine()->GetSwapChain(), GetEngine()->GetDepthResource(), GetEngine()->GetCommandPool(), GetEngine()->GetDescriptionSetLayout() };
    l_texParams.m_texturePath = a_path;
    m_texture = ResourceManager::GetInstance().LoadResource<VulkanTexture>(l_texParams);
}


void ModelComponent::SetMeshPath(const std::string& a_path)
{
    m_pendingMeshPath = a_path;
    m_shouldLoadResources = true;
}


void ModelComponent::SetTexturePath(const std::string& a_path)
{
    m_pendingTexturePath = a_path;
    m_shouldLoadResources = true;
}
