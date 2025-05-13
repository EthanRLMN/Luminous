#include "Game/Systems/Component/RigidbodyComponent.hpp"

#include "Game/Systems/Entity/Entity.hpp"
#include "Engine.hpp"

void RigidbodyComponent::Initialize()
{

	m_collisionDebugModel = new ModelComponent();

	m_collisionDebugModel->SetEngine(GetEngine());

	m_collisionDebugModel->SetMeshPath("Engine/Assets/Default/Models/colliderCube.obj");
    m_collisionDebugModel->SetTexturePath("Engine/Assets/Default/Textures/colliderTexture.png");
	//Set le mesh en fonction du type de collider
    m_collisionDebugModel->Initialize();

    TransformComponent* l_transform = m_entity.lock().get()->GetComponent<TransformComponent>().get();
    JPH::Vec3 l_position = JPH::Vec3(l_transform->GetLocalPosition().x, l_transform->GetLocalPosition().y, l_transform->GetLocalPosition().z);
    JPH::Vec3 l_scale = JPH::Vec3(l_transform->GetLocalScale().x, l_transform->GetLocalScale().y, l_transform->GetLocalScale().z);
    JPH::Quat l_rotation = JPH::Quat(l_transform->GetLocalRotationQuat().w, l_transform->GetLocalRotationQuat().x, l_transform->GetLocalRotationQuat().y, l_transform->GetLocalRotationQuat().z);

	JPH::BoxShapeSettings settings(l_scale);
    settings.SetEmbedded();
    JPH::ShapeSettings::ShapeResult floor_shape_result = settings.Create();
    JPH::ShapeRefC floor_shape = floor_shape_result.Get();

    PhysicsSystem* l_phys = GetEngine()->GetPhysicsSystem();

    m_rigidbody = GetEngine()->GetPhysicsSystem()->CreateRigidBody(floor_shape, l_position, l_rotation);
    m_rigidbody->SetParentComponent(this);
    m_rigidbody->SetIsSensor(true);



}

