#pragma once
#include <memory>
#include <vector>

#include "Game/Systems/Physics/PhysicsCollisionListener.hpp"
#include "Game/Systems/Component/ModelComponent.hpp"
#include "Game/Systems/Physics/RigidBody.hpp"
#include "Game/Systems/Physics/LayerSystem.hpp"


enum ColliderType
{
    BOXCOLLIDER = 0,
    SPHERECOLLIDER = 1,
    CAPSULECOLLIDER = 2
};

class  RigidbodyComponent : public EntityComponent
{
public:
    ~RigidbodyComponent() override = default;
    void Initialize() override;
    void GameplayStarted() override{};
    void Update() override;

    
    
    inline void SetEntity(const std::weak_ptr<Entity>& a_relatedEntity) { m_entity = a_relatedEntity; }
    inline void SetColliderType(ColliderType a_type) { m_colliderType = a_type; }
    inline void SetLayer(JPH::uint8 a_layer) { m_layer = a_layer; }
    inline void SetActive(JPH::EActivation a_active) { m_active = a_active; }
    inline void SetCapsuleWidth(float a_width) { m_capsuleWidth = a_width; }
    inline void SetCapsuleHeight(float a_height) { m_capsuleHeight = a_height; }
    void SetCollider();
    void SetColliderShape();
    inline void SetColliderSize(Maths::Vector3 a_boxSize) { m_boxSizeOffset = a_boxSize; SetColliderShape();} //Set Collider size for a Box
    inline void SetColliderSize(Maths::Vector2 a_capsuleSize) { m_capsuleSizeOffset = a_capsuleSize; SetCollider(); } //Set Collider size for a Capsule
    inline void SetColliderSize(float a_sphereSize) { m_sphereSizeOffset = a_sphereSize; SetCollider(); } //Set Collider size for a Sphere

    [[nodiscard]] inline std::shared_ptr<Entity> GetEntity() const { return m_entity.lock(); }
    inline ColliderType GetColliderType() { return m_colliderType; }
    inline ModelComponent* GetModelDebug() { return m_collisionDebugModel; }
    inline ModelComponent* GetCapsuleSphereDebug() { return m_capsuleDebugSphere; }
    inline JPH::EActivation GetActivation() { return m_active; }
    inline float GetCapsuleWidth() { return m_capsuleWidth; }
    inline float GetCapsuleHeight() { return m_capsuleHeight; }

    inline float GetSphereOffset() { return m_sphereSizeOffset; }
    inline Maths::Vector3 GetBoxOffset() { return m_boxSizeOffset; }
    inline Maths::Vector2 GetCapsuleOffset() { return m_capsuleSizeOffset; }

private:
    float m_capsuleWidth{ 0.0f };
    float m_capsuleHeight{ 0.0f };
    JPH::uint8 m_layer = Layers::KINEMATIC;
    std::weak_ptr<Entity> m_entity{};
    ModelComponent* m_collisionDebugModel;
    ModelComponent* m_capsuleDebugSphere;
    RigidBody* m_rigidbody;
    ColliderType m_colliderType = ColliderType::CAPSULECOLLIDER;
    JPH::EActivation m_active = JPH::EActivation::Activate;

    Maths::Vector3 m_boxSizeOffset{ 0.f, 0.f, 0.f };
    float m_sphereSizeOffset{ 2.0f };
    Maths::Vector2 m_capsuleSizeOffset{ 1.f, 2.f };
    Maths::Vector3 m_oldTransformSize{ 0.0f, 0.0f, 0.0f };
};

