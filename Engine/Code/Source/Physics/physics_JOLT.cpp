#include "Physics/physics_JOLT.hpp"
#include "Physics/listener.hpp"
#include "Physics/layers.hpp"

void Physics::Init_JOLT()
{

    RegisterDefaultAllocator();


    Trace = TraceImpl;
    JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)


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


    PhysicsSystem physics_system;
    physics_system.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, broad_phase_layer_interface, object_vs_broadphase_layer_filter, object_vs_object_layer_filter);


    MyBodyActivationListener body_activation_listener;
    physics_system.SetBodyActivationListener(&body_activation_listener);


    MyContactListener contact_listener;
    physics_system.SetContactListener(&contact_listener);


    BodyInterface& body_interface = physics_system.GetBodyInterface();


    BoxShapeSettings floor_shape_settings(Vec3(100.0f, 1.0f, 100.0f));
    floor_shape_settings.SetEmbedded(); 


    ShapeSettings::ShapeResult floor_shape_result = floor_shape_settings.Create();
    ShapeRefC floor_shape = floor_shape_result.Get(); 

    BodyCreationSettings floor_settings(floor_shape, JPH::RVec3(0.0f, -1.0f, 0.0f), Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);

    Body* floor = body_interface.CreateBody(floor_settings);


    body_interface.AddBody(floor->GetID(), EActivation::DontActivate);

    BodyCreationSettings sphere_settings(new SphereShape(0.5f), JPH::RVec3(0.0f, 2.0f, 0.0f), Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING);
    BodyID sphere_id = body_interface.CreateAndAddBody(sphere_settings, EActivation::Activate);

    body_interface.SetLinearVelocity(sphere_id, Vec3(0.0f, -5.0f, 0.0f));

    const float cDeltaTime = 1.0f / 60.0f;

    physics_system.OptimizeBroadPhase();


    uint step = 0;
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

