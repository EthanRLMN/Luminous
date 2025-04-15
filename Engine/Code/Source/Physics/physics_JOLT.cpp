#include "Physics/physics_JOLT.hpp"
#include "Physics/listener.hpp"
#include "Physics/layers.hpp"

void Physics::Init_JOLT()
{
    Factory::sInstance = new Factory();
    RegisterTypes();




    const uint cMaxBodies = 1024;


    const uint cNumBodyMutexes = 0;


    const uint cMaxBodyPairs = 1024;

    const uint cMaxContactConstraints = 1024;


    BPLayerInterfaceImpl broad_phase_layer_interface;
    ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;
    ObjectLayerPairFilterImpl object_vs_object_layer_filter;

    m_physicsSystem = new JPH::PhysicsSystem();
    m_physicsSystem->Init(cMaxBodies,cNumBodyMutexes,cMaxBodyPairs,cMaxContactConstraints,broad_phase_layer_interface,object_vs_broadphase_layer_filter,object_vs_object_layer_filter);


    m_bodyInterface = &m_physicsSystem->GetBodyInterface();
}

void Physics::Update_JOLT(float _deltaTime)
{
   // m_physicsSystem->Update(_deltaTime, cCollisionSteps, &temp_allocator, &job_system);
}



void Physics::Clean_JOLT()
{

}

JPH::Body* Physics::CreateBody()
{
    return nullptr;
}

