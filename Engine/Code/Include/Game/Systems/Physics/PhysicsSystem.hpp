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


class PhysicsSystem
{
public:
    struct Settings
    {
        JPH::uint m_maxRigidBodies { 1024 * 32 }; // Number of rigid bodies that can be added to the Physics System
        JPH::uint m_bodyMutexNumber { 0 }; // Determines how many mutexes to allocate to protect rigid bodies from concurrent access. 0 for the default settings
        JPH::uint m_maxBodyPairs { 1024 * 16 }; // Max number of body pairs that can be queued at any time
        JPH::uint m_maxContactConstraints { 1024 * 6 }; // Max size of the contact constraint buffer.
    };

    PhysicsSystem() = default;
    ~PhysicsSystem() = default;

    void Init(const Settings& a_settings);
    void Update();
    void Destroy();
    void TriggerPhysicsOptimization() const;


    inline JPH::BodyInterface& GetBodyInterface() const { return m_physicsSystem->GetBodyInterface(); }

private:
    JPH::PhysicsSystem* m_physicsSystem{ nullptr };
    JPH::uint m_currentStep { 0 };

    JPH::BodyID m_sphereId{ };
    JPH::Body* m_floor{ nullptr };
    JPH::BPLayerInterfaceImpl* m_broadPhaseLayerInterface{ nullptr };
    JPH::ObjectVsBroadPhaseLayerFilterImpl* m_ObjToBroadPhaseLayerFilter{ nullptr };
    JPH::ObjectLayerPairFilterImpl* m_ObjToObjLayerFilter{ nullptr };

    JPH::TempAllocatorImpl* m_tempAllocator{ nullptr };
    JPH::JobSystemThreadPool* m_jobSystem{ nullptr };

    JPH::MyBodyActivationListener* m_bodyActivationListener{ nullptr };
    JPH::MyContactListener* m_contactListener{ nullptr };
    JPH::BoxShapeSettings* m_floorShapeSettings { nullptr };
    JPH::ShapeSettings::ShapeResult m_floorShapeResult;
    JPH::ShapeRefC m_floorShape;

    JPH::BodyCreationSettings* m_floorSettings{ nullptr };
    JPH::BodyCreationSettings* m_sphereSettings{ nullptr };

    std::vector<JPH::Body*> m_rigidBodies{ };
};


