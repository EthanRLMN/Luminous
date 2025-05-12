#pragma once

#include <vector>

#include "RigidBody.hpp"
#include "Vector3.hpp"
#include "Jolt/Jolt.h"
#include "Jolt/Physics/PhysicsSystem.h"
#include "Jolt/Physics/Body/Body.h"
#include "Jolt/Physics/Body/BodyID.h"

#include "Game/Systems/Physics/LayerSystem.hpp"
#include "Jolt/Physics/Collision/Shape/BoxShape.h"
#include "Jolt/Physics/Collision/Shape/SphereShape.h"

enum class PhysicsCollisionEvent;
class PhysicsBodyActivationListener;

namespace JPH {
    class JobSystemThreadPool;
    class BodyInterface;
    class Body;
    class BoxShapeSettings;
}


class PhysicsSystem
{
public:
    struct Settings
    {
        JPH::uint m_maxRigidBodies { 1024 * 32 }; // Number of rigid bodies that can be added to the Physics System
        JPH::uint m_bodyMutexNumber { 0 }; // Determines how many mutexes to allocate to protect rigid bodies from concurrent access. 0 for the default settings
        JPH::uint m_maxBodyPairs { 1024 * 16 }; // Max number of body pairs that can be queued at any time
        JPH::uint m_maxContactConstraints { 1024 * 6 }; // Max size of the contact constraint buffer.

        float m_gravity { 9.81f }; // Default value for gravity
        float m_gravityFactor { 1.0f }; // The gravity factor
    };

    PhysicsSystem() = default;
    ~PhysicsSystem() = default;

    void Init(const Settings& a_settings);
    void Update();
    void Destroy();
    void TriggerPhysicsOptimization() const;

    [[nodiscard]] inline JPH::BodyInterface& GetBodyInterface() const { return m_physicsSystem->GetBodyInterface(); }
    [[nodiscard]] inline JPH::PhysicsSystem* GetPhysicsSystem() const { return m_physicsSystem; }
    [[nodiscard]] inline JPH::JobSystemThreadPool* GetJobSystem() const { return m_jobSystem; }
    [[nodiscard]] inline JPH::TempAllocatorImpl* GetTempAllocator() const { return m_tempAllocator; }
    [[nodiscard]] inline JPH::BroadPhaseLayerInterface* GetBroadPhaseLayerInterface() const { return m_broadPhaseLayerInterface; }
    [[nodiscard]] inline JPH::ObjectVsBroadPhaseLayerFilter* GetObjectToBroadPhaseLayerFilter() const { return m_ObjToBroadPhaseLayerFilter; }
    [[nodiscard]] inline JPH::ObjectLayerPairFilter* GetObjectToObjLayerFilter() const { return m_ObjToObjLayerFilter; }
    [[nodiscard]] inline JPH::BodyActivationListener* GetBodyActivationListener() const { return m_bodyActivationListener; }
    [[nodiscard]] inline JPH::ContactListener* GetContactListener() const { return m_collisionListener; }
    [[nodiscard]] inline std::vector<RigidBody*> GetRigidBodies() const { return m_rigidBodies; }
    [[nodiscard]] inline std::unordered_map<JPH::BodyID, RigidBody*> GetRigidBodyMap() const { return m_bodiesToRigidBodies; }



    void NotifyCollisionEnter(PhysicsCollisionEvent a_collisionEvent, const JPH::BodyID& a_body1, const JPH::BodyID& a_body2);
    void NotifyCollisionExit(PhysicsCollisionEvent a_collisionEvent, const JPH::BodyID& a_body1, const JPH::BodyID& a_body2);


    /*          Body Creation Functions          */
    RigidBody* CreateRigidBody(const JPH::Shape* a_shape, JPH::uint8 a_layer = Layers::DYNAMIC);
    RigidBody* CreateBox(Maths::Vector3 a_scale = Maths::Vector3::One);
    inline RigidBody* CreateSphere(const float a_radius = 1.0f) { return CreateRigidBody(new JPH::SphereShape(a_radius)); };
    void RemoveBody(const JPH::BodyID& a_bodyId);
    void RemoveAllBodies();

    
private:
    JPH::PhysicsSystem* m_physicsSystem { nullptr };

    JPH::BodyID m_sphereId{};
    //JPH::Body* m_floor { nullptr };
    JPH::BroadPhaseLayerInterface* m_broadPhaseLayerInterface { nullptr };
    JPH::ObjectVsBroadPhaseLayerFilter* m_ObjToBroadPhaseLayerFilter { nullptr };
    JPH::ObjectLayerPairFilter* m_ObjToObjLayerFilter { nullptr };

    JPH::TempAllocatorImpl* m_tempAllocator { nullptr };
    JPH::JobSystemThreadPool* m_jobSystem { nullptr };

    JPH::BodyActivationListener* m_bodyActivationListener { nullptr };
    JPH::ContactListener* m_collisionListener { nullptr };
    //JPH::BoxShapeSettings* m_floorShapeSettings { nullptr };
    JPH::ShapeSettings::ShapeResult m_floorShapeResult;
    JPH::ShapeRefC m_floorShape;

    //JPH::BodyCreationSettings* m_floorSettings { nullptr };
    //JPH::BodyCreationSettings* m_sphereSettings { nullptr };

    std::vector<RigidBody*> m_rigidBodies{};
    std::unordered_map<JPH::BodyID, RigidBody*> m_bodiesToRigidBodies;

    RigidBody* l_rigidbodySource;
    RigidBody* l_rigidbodySource2;
};


