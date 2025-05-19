#include "Game/Systems/Component/RigidbodyComponent.hpp"

#include "Game/Systems/Entity/Entity.hpp"
#include "Engine.hpp"
#include "Jolt/Physics/Collision/Shape/CapsuleShape.h"

#include "Game/Systems/Physics/PhysicsSystem.hpp"

void RigidbodyComponent::Initialize()
{
    InitDebugModels();
    SetCollider();
}

void RigidbodyComponent::Update()
{
    if (m_entity.expired())
        return;
    if (m_rigidbody == nullptr)
        return;
    
    if (TransformComponent* l_transform = m_entity.lock()->Transform().get())
    {
        if (l_transform->GetLocalScale() != m_oldTransformSize)
        {   
            SetColliderShape();
            
        }

         if (l_transform->GetLocalPosition() != m_oldPosition || l_transform->GetLocalRotationVec() != m_oldRotation)
        {
            UpdateTransform();
        }

        
    }

}

void RigidbodyComponent::UpdateTransform()
{
    TransformComponent* l_transform = m_entity.lock()->Transform().get();
    m_oldPosition = l_transform->GetLocalPosition();
    m_oldRotation = l_transform->GetLocalRotationVec();

    JPH::Vec3 l_position = JPH::Vec3(l_transform->GetLocalPosition().x, l_transform->GetLocalPosition().y, l_transform->GetLocalPosition().z);
    JPH::Quat l_rotation = JPH::Quat(l_transform->GetLocalRotationQuat().x, l_transform->GetLocalRotationQuat().y, l_transform->GetLocalRotationQuat().z, l_transform->GetLocalRotationQuat().w);
    m_oldTransformSize = l_transform->GetLocalScale();

    GetEngine()->GetPhysicsSystem()->GetBodyInterface().SetPosition(m_rigidbody->GetRigidBody()->GetID(), l_position,m_active);
    GetEngine()->GetPhysicsSystem()->GetBodyInterface().SetRotation(m_rigidbody->GetRigidBody()->GetID(), l_rotation, m_active);
}

void RigidbodyComponent::SetLayer(JPH::uint8 a_layer)
{
    m_layer = a_layer;
    if (m_rigidbody)
    {
        GetEngine()->GetPhysicsSystem()->GetBodyInterface().SetObjectLayer(m_rigidbody->GetRigidBody()->GetID(), m_layer);
        JPH::EMotionType l_motionType = JPH::EMotionType::Static;


        if (m_layer == Layers::DYNAMIC)
        {
            GetEngine()->GetPhysicsSystem()->GetBodyInterface().ActivateBody(m_rigidbody->GetRigidBody()->GetID());
            l_motionType = JPH::EMotionType::Dynamic;
        } else if (m_layer == Layers::KINEMATIC)
        {
            GetEngine()->GetPhysicsSystem()->GetBodyInterface().DeactivateBody(m_rigidbody->GetRigidBody()->GetID());
            l_motionType = JPH::EMotionType::Kinematic;
        } else
            l_motionType = JPH::EMotionType::Static;
        m_rigidbody->SetMotionType(l_motionType);
    }
}

void RigidbodyComponent::InitDebugModels()
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
}

void RigidbodyComponent::SetCollider()
{

    Entity* l_entity = m_entity.lock().get();
    TransformComponent* l_transform = m_entity.lock().get()->GetComponent<TransformComponent>().get();
    JPH::Vec3 l_position = JPH::Vec3(l_transform->GetLocalPosition().x, l_transform->GetLocalPosition().y, l_transform->GetLocalPosition().z);
    JPH::Vec3 l_scale = JPH::Vec3(l_transform->GetLocalScale().x, l_transform->GetLocalScale().y , l_transform->GetLocalScale().z);
    JPH::Quat l_rotation = JPH::Quat(l_transform->GetLocalRotationQuat().x, l_transform->GetLocalRotationQuat().y, l_transform->GetLocalRotationQuat().z, l_transform->GetLocalRotationQuat().w);
    m_oldTransformSize = l_transform->GetLocalScale();

    if (m_colliderType == ColliderType::BOXCOLLIDER)
    {
        l_scale += JPH::Vec3(m_boxSizeOffset.x, m_boxSizeOffset.y, m_boxSizeOffset.z);
        JPH::BoxShapeSettings settings(l_scale);
        settings.SetEmbedded();
        JPH::ShapeSettings::ShapeResult floor_shape_result = settings.Create();
        JPH::ShapeRefC floor_shape = floor_shape_result.Get();


        m_rigidbody = GetEngine()->GetPhysicsSystem()->CreateRigidBody(floor_shape, l_position, l_rotation, m_layer, m_active);
        m_rigidbody->SetParentComponent(this); 
    } else if (m_colliderType == ColliderType::SPHERECOLLIDER)
    {
        JPH::SphereShapeSettings settings(l_scale.GetY() + m_sphereSizeOffset);
        settings.SetEmbedded();
        JPH::ShapeSettings::ShapeResult floor_shape_result = settings.Create();
        JPH::ShapeRefC floor_shape = floor_shape_result.Get();


        m_rigidbody = GetEngine()->GetPhysicsSystem()->CreateRigidBody(floor_shape, l_position, l_rotation, m_layer, m_active);
        m_rigidbody->SetParentComponent(this);
    } else if (m_colliderType == ColliderType::CAPSULECOLLIDER)
    {
        float l_maxWidth = l_scale.GetX();
        if (l_scale.GetZ() > l_scale.GetX())
            l_maxWidth = l_scale.GetZ();
        else
            l_maxWidth = l_scale.GetX();

        JPH::CapsuleShapeSettings settings(l_scale.GetY() + m_capsuleSizeOffset.y, l_maxWidth + m_capsuleSizeOffset.x);
        settings.SetEmbedded();
        JPH::ShapeSettings::ShapeResult floor_shape_result = settings.Create();
        JPH::ShapeRefC floor_shape = floor_shape_result.Get();
        m_capsuleWidth = l_maxWidth;
        m_capsuleHeight = l_scale.GetY();


        m_rigidbody = GetEngine()->GetPhysicsSystem()->CreateRigidBody(floor_shape, l_position, l_rotation, m_layer, m_active);
        m_rigidbody->SetParentComponent(this);
    }
    

}

void RigidbodyComponent::SetColliderShape()
{

    TransformComponent* l_transform = m_entity.lock()->GetComponent<TransformComponent>().get();
    JPH::Vec3 l_scale = JPH::Vec3(l_transform->GetLocalScale().x, l_transform->GetLocalScale().y, l_transform->GetLocalScale().z);

    if (m_colliderType == ColliderType::BOXCOLLIDER)
    {

        l_scale += JPH::Vec3(m_boxSizeOffset.x, m_boxSizeOffset.y, m_boxSizeOffset.z);
        JPH::BoxShapeSettings settings(l_scale);
        settings.SetEmbedded();
        JPH::ShapeSettings::ShapeResult floor_shape_result = settings.Create();
        JPH::ShapeRefC floor_shape = floor_shape_result.Get();
        GetEngine()->GetPhysicsSystem()->GetBodyInterface().SetShape(m_rigidbody->GetRigidBody()->GetID(),floor_shape,true,m_active);

    }
    else if (m_colliderType == ColliderType::SPHERECOLLIDER)
    {
        JPH::SphereShapeSettings settings(l_scale.GetY() + m_sphereSizeOffset);
        settings.SetEmbedded();
        JPH::ShapeSettings::ShapeResult floor_shape_result = settings.Create();
        JPH::ShapeRefC floor_shape = floor_shape_result.Get();


        GetEngine()->GetPhysicsSystem()->GetBodyInterface().SetShape(m_rigidbody->GetRigidBody()->GetID(), floor_shape, true, m_active);
    }
    else if (m_colliderType == ColliderType::CAPSULECOLLIDER)
    {
        float l_maxWidth = l_scale.GetX();
        if (l_scale.GetZ() > l_scale.GetX())
            l_maxWidth = l_scale.GetZ();
        else
            l_maxWidth = l_scale.GetX();

        JPH::CapsuleShapeSettings settings(l_scale.GetY() + m_capsuleSizeOffset.y, l_maxWidth + m_capsuleSizeOffset.x);
        settings.SetEmbedded();
        JPH::ShapeSettings::ShapeResult floor_shape_result = settings.Create();
        JPH::ShapeRefC floor_shape = floor_shape_result.Get();
        m_capsuleWidth = l_maxWidth;
        m_capsuleHeight = l_scale.GetY();

        GetEngine()->GetPhysicsSystem()->GetBodyInterface().SetShape(m_rigidbody->GetRigidBody()->GetID(), floor_shape, true, m_active);
    }
}

