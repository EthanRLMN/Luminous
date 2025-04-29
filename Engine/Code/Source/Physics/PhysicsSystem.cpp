#include "Physics/PhysicsSystem.hpp"

#include <thread>

#include "Game/Systems/Time.inl"
#include "Jolt/RegisterTypes.h"
#include "Jolt/Core/Factory.h"
#include "Jolt/Core/Memory.h"
#include "Jolt/Physics/PhysicsSettings.h"
#include "Physics/Layers.hpp"
#include "Physics/Listener.hpp"


void PhysicsSystem::Init(const Settings& a_settings)
{
    JPH::RegisterDefaultAllocator();
    JPH::Factory::sInstance = new JPH::Factory();
    JPH::RegisterTypes();

    m_tempAllocator = new JPH::TempAllocatorImpl(10 * 1024 * 1024);
    m_jobSystem = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, static_cast<int>(std::thread::hardware_concurrency()) - 1);

    m_broadPhaseLayerInterface = new JPH::BPLayerInterfaceImpl();
    m_ObjToBroadPhaseLayerFilter = new JPH::ObjectVsBroadPhaseLayerFilterImpl();
    m_ObjToObjLayerFilter = new JPH::ObjectLayerPairFilterImpl();

    m_physicsSystem = new JPH::PhysicsSystem();
    m_physicsSystem->Init(a_settings.m_maxRigidBodies, a_settings.m_bodyMutexNumber, a_settings.m_maxBodyPairs, a_settings.m_maxContactConstraints, *m_broadPhaseLayerInterface, *m_ObjToBroadPhaseLayerFilter, *m_ObjToObjLayerFilter);

    m_physicsSystem->SetBodyActivationListener(m_bodyActivationListener);
    m_physicsSystem->SetContactListener(m_contactListener);

    m_floorShapeSettings = new JPH::BoxShapeSettings(JPH::Vec3(100.0f, 1.0f, 100.0f));
    m_floorShapeSettings->SetEmbedded();


    m_floorShapeResult = m_floorShapeSettings->Create();
    m_floorShape = m_floorShapeResult.Get();

    m_floorSettings = new JPH::BodyCreationSettings(m_floorShape, JPH::RVec3(0.0f, -1.0f, 0.0f), JPH::Quat::sIdentity(), JPH::EMotionType::Static, JPH::Layers::NON_MOVING);

    m_floor = GetBodyInterface().CreateBody(*m_floorSettings);


    GetBodyInterface().AddBody(m_floor->GetID(), JPH::EActivation::DontActivate);

    m_sphereSettings = new JPH::BodyCreationSettings(new JPH::SphereShape(0.5f), JPH::RVec3(0.0f, 2.0f, 0.0f), JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, JPH::Layers::MOVING);
    m_sphereId = GetBodyInterface().CreateAndAddBody(*m_sphereSettings, JPH::EActivation::Activate);

    GetBodyInterface().SetLinearVelocity(m_sphereId, JPH::Vec3(0.0f, -5.0f, 0.0f));

    m_physicsSystem->OptimizeBroadPhase();
    m_currentStep = 0;
}

void PhysicsSystem::Update()
{
    if (!GetBodyInterface().IsActive(m_sphereId))
        return;

    ++m_currentStep;

    JPH::RVec3 position = GetBodyInterface().GetCenterOfMassPosition(m_sphereId);
    JPH::Vec3 velocity = GetBodyInterface().GetLinearVelocity(m_sphereId);
    std::cout << "Step " << m_currentStep << ": Position = (" << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << "), Velocity = (" << velocity.GetX() << ", " << velocity.GetY() << ", " << velocity.GetZ() << ")" << std::endl;

    const int cCollisionSteps = 1;
    // Step the world
    m_physicsSystem->Update(Time::GetFixedDeltaTime(), cCollisionSteps, m_tempAllocator, m_jobSystem);
}


void PhysicsSystem::Clean()
{
    GetBodyInterface().RemoveBody(m_sphereId);
    GetBodyInterface().DestroyBody(m_sphereId);

    GetBodyInterface().RemoveBody(m_floor->GetID());
    GetBodyInterface().DestroyBody(m_floor->GetID());

    JPH::UnregisterTypes();

    delete JPH::Factory::sInstance;
    JPH::Factory::sInstance = nullptr;
}

JPH::Body* PhysicsSystem::CreateBody() { return nullptr; }

JPH::BodyInterface& PhysicsSystem::GetBodyInterface() const { return m_physicsSystem->GetBodyInterface(); }

