#include "Game/Systems/Component/RigidbodyComponent.hpp"

void RigidbodyComponent::Initialize()
{

	m_collisionDebugModel = new ModelComponent();

	m_collisionDebugModel->SetEngine(GetEngine());

	m_collisionDebugModel->SetMeshPath("Engine/Assets/Default/Models/colliderCube.obj");
    m_collisionDebugModel->SetTexturePath("Engine/Assets/Default/Textures/colliderTexture.png");
	//Set le mesh en fonction du type de collider
    m_collisionDebugModel->Initialize();

}
