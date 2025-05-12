#include "Game/Systems/Component/RigidbodyComponent.hpp"

void RigidbodyComponent::Initialize()
{

	m_collisionDebugModel = new ModelComponent();
	//Set le mesh en fonction du type de collider
    m_collisionDebugModel->Initialize();
}
