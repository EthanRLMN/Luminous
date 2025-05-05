#include "Game/Systems/Physics/PhysicsSystem.hpp"

#include <thread>

#include "Jolt/RegisterTypes.h"
#include "Jolt/Core/Factory.h"
#include "Jolt/Core/Memory.h"
#include "Jolt/Physics/PhysicsSettings.h"

#include "Game/Systems/Time.inl"
#include "Game/Systems/Physics/Layers.hpp"
#include "Game/Systems/Physics/Listener.hpp"
#include "Jolt/Core/JobSystemThreadPool.h"


// Default value for the TempAllocator (10MB by default)
constexpr JPH::uint32 TempAllocatorSize = 10 * 1024 * 1024;


void PhysicsSystem::Init(const Settings& a_settings)
{
    JPH::RegisterDefaultAllocator(); // Register the memory allocator (Default is malloc)

    JPH::Factory::sInstance = new JPH::Factory(); // Set up the factory used for creating instances of classes based on their names
    JPH::RegisterTypes(); // Register all physics types with the factory and install their collision handlers with the CollisionDispatch class

    m_tempAllocator = new JPH::TempAllocatorImpl(TempAllocatorSize); // Set up the temporary allocator size
    m_jobSystem = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, static_cast<int>(std::thread::hardware_concurrency()) - 1); // Init the job system to execute physics on multiple threads

    m_broadPhaseLayerInterface = new JPH::BPLayerInterfaceImpl(); // Create a mapping table from object layer to broad phase layer
    m_ObjToBroadPhaseLayerFilter = new JPH::ObjectVsBroadPhaseLayerFilterImpl(); // Create a class that filters object vs. broad phase layers
    m_ObjToObjLayerFilter = new JPH::ObjectLayerPairFilterImpl(); // Create a class that filters object vs. object layers

    m_physicsSystem = new JPH::PhysicsSystem(); // Create the physics system and initialize it with all the previous data
    m_physicsSystem->Init(a_settings.m_maxRigidBodies, a_settings.m_bodyMutexNumber, a_settings.m_maxBodyPairs, a_settings.m_maxContactConstraints, *m_broadPhaseLayerInterface, *m_ObjToBroadPhaseLayerFilter, *m_ObjToObjLayerFilter);

    m_bodyActivationListener = new JPH::PhysicsBodyActivationListener(); // Create a body activation listener that gets notified when bodies activate and go to sleep | MUST BE THREAD SAFE
    m_physicsSystem->SetBodyActivationListener(m_bodyActivationListener);

    m_contactListener = new JPH::PhysicsContactListener(); // Create a contact listener that gets notified when bodies (are about to) collide, and when they separate again | MUST BE THREAD SAFE
    m_physicsSystem->SetContactListener(m_contactListener);
}


void PhysicsSystem::Update()
{
    for (const JPH::Body* l_rigidBody : m_rigidBodies)
        if (!GetBodyInterface().IsActive(l_rigidBody->GetID()))
            return;

    // TODO : Update collision steps to run properly (accumulator returns floats on a scale from 0.25 to 10, we need integers scaled properly)
    constexpr int l_step { 1 };

    m_physicsSystem->Update(Time::GetFixedDeltaTime(), l_step, m_tempAllocator, m_jobSystem);
}


void PhysicsSystem::Destroy()
{
    for (const JPH::Body* l_rigidBody : m_rigidBodies)
    {
        GetBodyInterface().RemoveBody(l_rigidBody->GetID());
        GetBodyInterface().DestroyBody(l_rigidBody->GetID());
    }

    delete m_contactListener;
    m_contactListener = nullptr;

    delete m_bodyActivationListener;
    m_bodyActivationListener = nullptr;

    delete m_physicsSystem;
    m_physicsSystem = nullptr;

    delete m_ObjToObjLayerFilter;
    m_ObjToObjLayerFilter = nullptr;

    delete m_ObjToBroadPhaseLayerFilter;
    m_ObjToBroadPhaseLayerFilter = nullptr;

    delete m_broadPhaseLayerInterface;
    m_broadPhaseLayerInterface = nullptr;

    delete m_jobSystem;
    m_jobSystem = nullptr;

    delete m_tempAllocator;
    m_tempAllocator = nullptr;

    JPH::UnregisterTypes();
    delete JPH::Factory::sInstance;
    JPH::Factory::sInstance = nullptr;
}

void PhysicsSystem::TriggerPhysicsOptimization() const
{
    m_physicsSystem->OptimizeBroadPhase();
}

