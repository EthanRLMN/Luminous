#include "Physics/physics_JOLT.hpp"

void Physics::Init_JOLT()
{
    Factory::sInstance = new Factory();
    RegisterTypes();


    TempAllocatorImpl temp_allocator(10 * 1024 * 1024);

    JobSystemThreadPool job_system(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);

    const uint cMaxBodies = 1024;


    const uint cNumBodyMutexes = 0;


    const uint cMaxBodyPairs = 1024;

    const uint cMaxContactConstraints = 1024;


    BPLayerInterfaceImpl broad_phase_layer_interface;
    ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;
    ObjectLayerPairFilterImpl object_vs_object_layer_filter;

    m_physicsSystem = new JPH::PhysicsSystem();
    m_physicsSystem->Init();


    m_bodyInterface = &m_physicsSystem->GetBodyInterface();
}

void Physics::Update_JOLT(float _deltaTime)
{
    m_physicsSystem->Update(_deltaTime,);
}



void Physics::Clean_JOLT()
{

}

JPH::Body* Physics::CreateBody(float _radius)
{

    JPH::BodyCreationSettings settings;


    JPH::Body* body = m_bodyInterface->CreateBody(settings);
    return body;
}

