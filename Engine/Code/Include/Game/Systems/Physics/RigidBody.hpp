#pragma once

#include "Jolt/Jolt.h"
#include "Jolt/Physics/PhysicsSystem.h"
#include "Jolt/Physics/Body/Body.h"
#include "Jolt/Physics/Body/BodyID.h"

namespace JPH {
    class JobSystemThreadPool;
    class ObjectLayerPairFilterImpl;
    class ObjectVsBroadPhaseLayerFilterImpl;
    class BPLayerInterfaceImpl;
    class PhysicsSystem;
    class BodyInterface;
    class Body;
    class TempAllocatorImpl;
    class MyBodyActivationListener;
    class MyContactListener;
    class BoxShapeSettings;
}


class RigidBody
{
public:
    RigidBody() = default;
    ~RigidBody() { delete m_rigidBody; m_rigidBody = nullptr; };

    inline JPH::Body* GetRigidBody() const { return m_rigidBody; }
    inline JPH::BodyID GetRigidBodyID() const { return GetRigidBody()->GetID(); }
    inline JPH::EBodyType GetRigidBodyType() const { return GetRigidBody()->GetBodyType(); }
    inline JPH::MotionProperties* GetMotionProperties() const { return GetRigidBody()->GetMotionProperties(); }
    inline JPH::EMotionType GetMotionType() const { return GetRigidBody()->GetMotionType(); }
    inline bool IsRigidBody() const { return GetRigidBodyType() == JPH::EBodyType::RigidBody; }
    inline bool IsSoftBody() const { return GetRigidBodyType() == JPH::EBodyType::SoftBody; }
    inline bool IsActive() const { return GetMotionProperties() != nullptr && GetMotionProperties()->GetIndexInActiveBodiesInternal() != GetRigidBody()->cInactiveIndex; }
    inline bool IsStatic() const { return GetMotionType() == JPH::EMotionType::Static; }
    inline bool IsKinematic() const { return GetMotionType() == JPH::EMotionType::Kinematic; }
    inline bool IsDynamic() const { return GetMotionType() == JPH::EMotionType::Dynamic; }
    inline bool CanBeKinematicOrDynamic() const { return GetMotionProperties() != nullptr; }
    //inline bool IsSensor() const { return (mFlags.load(memory_order_relaxed) & uint8(EFlags::IsSensor)) != 0; }

private:
    JPH::Body* m_rigidBody { nullptr };
};
