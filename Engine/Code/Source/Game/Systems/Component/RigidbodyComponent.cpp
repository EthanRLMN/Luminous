#include "Game/Systems/Component/RigidbodyComponent.hpp"

#include "Game/Systems/Entity/Entity.hpp"
#include "Engine.hpp"
#include "Jolt/Physics/Collision/Shape/CapsuleShape.h"

void RigidbodyComponent::Initialize()
{

	m_collisionDebugModel = new ModelComponent();
    m_capsuleDebugSphere = new ModelComponent();

	m_collisionDebugModel->SetEngine(GetEngine());
    m_capsuleDebugSphere->SetEngine(GetEngine());

    m_collisionDebugModel->SetTexturePath("Engine/Assets/Default/Textures/colliderTexture.png");
    m_capsuleDebugSphere->SetTexturePath("Engine/Assets/Default/Textures/colliderTexture.png");

    if (m_colliderType == ColliderType::BOXCOLLIDER)
    {
        m_collisionDebugModel->SetMeshPath("Engine/Assets/Default/Models/colliderCube.obj");
    } else if (m_colliderType == ColliderType::SPHERECOLLIDER)
    {
        m_collisionDebugModel->SetMeshPath("Engine/Assets/Default/Models/colliderSphere.obj");
    } else if (m_colliderType == ColliderType::CAPSULECOLLIDER)
    {
        m_collisionDebugModel->SetMeshPath("Engine/Assets/Default/Models/colliderCylinder.obj");
        m_capsuleDebugSphere->SetMeshPath("Engine/Assets/Default/Models/colliderSphere.obj");
        m_capsuleDebugSphere->Initialize();
    }
	

    m_collisionDebugModel->Initialize();

    TransformComponent* l_transform = m_entity.lock().get()->GetComponent<TransformComponent>().get();
    JPH::Vec3 l_position = JPH::Vec3(l_transform->GetLocalPosition().x, l_transform->GetLocalPosition().y, l_transform->GetLocalPosition().z);
    JPH::Vec3 l_scale = JPH::Vec3(l_transform->GetLocalScale().x, l_transform->GetLocalScale().y, l_transform->GetLocalScale().z);
    JPH::Quat l_rotation = JPH::Quat(l_transform->GetLocalRotationQuat().x, l_transform->GetLocalRotationQuat().y, l_transform->GetLocalRotationQuat().z, l_transform->GetLocalRotationQuat().w);


    if (m_colliderType == ColliderType::BOXCOLLIDER)
    {
        JPH::BoxShapeSettings settings(l_scale);
        settings.SetEmbedded();
        JPH::ShapeSettings::ShapeResult floor_shape_result = settings.Create();
        JPH::ShapeRefC floor_shape = floor_shape_result.Get();


        PhysicsSystem* l_phys = GetEngine()->GetPhysicsSystem();

        m_rigidbody = GetEngine()->GetPhysicsSystem()->CreateRigidBody(floor_shape, l_position, l_rotation, m_layer, m_active);
        m_rigidbody->SetParentComponent(this);
    }
    else if (m_colliderType == ColliderType::SPHERECOLLIDER)
    {
        JPH::SphereShapeSettings settings(l_scale.GetY());
        settings.SetEmbedded();
        JPH::ShapeSettings::ShapeResult floor_shape_result = settings.Create();
        JPH::ShapeRefC floor_shape = floor_shape_result.Get();


        PhysicsSystem* l_phys = GetEngine()->GetPhysicsSystem();

        m_rigidbody = GetEngine()->GetPhysicsSystem()->CreateRigidBody(floor_shape, l_position, l_rotation, m_layer, m_active);
        m_rigidbody->SetParentComponent(this);
    } else if (m_colliderType == ColliderType::CAPSULECOLLIDER)
    {
        JPH::CapsuleShapeSettings settings(l_scale.GetY()/2,(l_scale.GetZ() + l_scale.GetX()) / 2);
        settings.SetEmbedded();
        JPH::ShapeSettings::ShapeResult floor_shape_result = settings.Create();
        JPH::ShapeRefC floor_shape = floor_shape_result.Get();


        PhysicsSystem* l_phys = GetEngine()->GetPhysicsSystem();

        m_rigidbody = GetEngine()->GetPhysicsSystem()->CreateRigidBody(floor_shape, l_position, l_rotation, m_layer, m_active);
        m_rigidbody->SetParentComponent(this);
    }

	
    //m_rigidbody->SetAllowSleeping(false);
    



}

