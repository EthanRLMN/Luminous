#include "Game/Systems/Component/ModelComponent.hpp"
#include "Engine.hpp"
#include "Rendering/Vulkan/VulkanBuffer.hpp"
#include "ResourceManager/ResourceManager.hpp"


void ModelComponent::Initialize()
{
    
    if (m_engine != nullptr) 
    {
        DEBUG_LOG_ERROR("ENGINE OK !");
    }

    SetMesh("Engine/Assets/Models/viking_room.obj");
    SetTexture("Engine/Assets/Textures/viking_room.png");
}

void ModelComponent::SetMesh(const std::string& a_path)
{
    
    IResourceParams l_meshParams{};
    l_meshParams.m_meshPath = a_path;
    m_mesh = ResourceManager::GetInstance().LoadResource<VulkanMesh>(l_meshParams);
    VulkanBuffer::SetMeshBuffers(m_engine->GetDevice(), m_engine->GetCommandPool(), m_mesh);

}

void ModelComponent::SetTexture(const std::string& a_path)
{ 
    IResourceParams l_texParams{ m_engine->GetDevice(), m_engine->GetSwapChain(), m_engine->GetDepthResource(), m_engine->GetCommandPool(), m_engine->GetDescriptionSetLayout() };
    l_texParams.m_texturePath = a_path;
    m_texture = ResourceManager::GetInstance().LoadResource<VulkanTexture>(l_texParams);
}
