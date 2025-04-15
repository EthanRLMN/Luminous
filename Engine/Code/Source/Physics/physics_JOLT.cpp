#include "Physics/physics_JOLT.hpp"
#include "Physics/listener.hpp"
#include "Physics/layers.hpp"


Physics::Physics() :
    temp_allocator(10 * 1024 * 1024) 
    ,
    job_system(cMaxPhysicsJobs, cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1), physics_system() 
    ,
    body_interface(physics_system.GetBodyInterface()) 
{
   
}



void Physics::Init_JOLT()
{

    RegisterDefaultAllocator();

    /*
    Trace = TraceImpl;
    JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)
        */

    Factory::sInstance = new Factory();

    RegisterTypes();

    const uint cMaxBodies = 1024;


    const uint cNumBodyMutexes = 0;


    const uint cMaxBodyPairs = 1024;


    const uint cMaxContactConstraints = 1024;


    BPLayerInterfaceImpl broad_phase_layer_interface;


    ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;

    ObjectLayerPairFilterImpl object_vs_object_layer_filter;


    
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
    sphere_id = body_interface.CreateAndAddBody(sphere_settings, EActivation::Activate);

    body_interface.SetLinearVelocity(sphere_id, Vec3(0.0f, -5.0f, 0.0f));

    cDeltaTime = 1.0f / 60.0f;

    physics_system.OptimizeBroadPhase();
    step = 0;
}

void Physics::Update_JOLT()
{

    ++step;


    RVec3 position = body_interface.GetCenterOfMassPosition(sphere_id);
    Vec3 velocity = body_interface.GetLinearVelocity(sphere_id);
    std::cout << "Step " << step << ": Position = (" << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << "), Velocity = (" << velocity.GetX() << ", " << velocity.GetY() << ", " << velocity.GetZ() << ")" << std::endl;

    const int cCollisionSteps = 1;
    // Step the world
    physics_system.Update(cDeltaTime, cCollisionSteps, &temp_allocator, &job_system);
}



void Physics::Clean_JOLT()
{

}

JPH::Body* Physics::CreateBody()
{
    return nullptr;
}

