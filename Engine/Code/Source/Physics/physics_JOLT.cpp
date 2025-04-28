#include "Physics/physics_JOLT.hpp"

#include <thread>

#include "Jolt/RegisterTypes.h"
#include "Jolt/Core/Factory.h"
#include "Jolt/Core/Memory.h"
#include "Jolt/Physics/PhysicsSettings.h"
#include "Physics/layers.hpp"
#include "Physics/listener.hpp"


void Physics::Init_JOLT()
{
    JPH::RegisterDefaultAllocator();
    JPH::Factory::sInstance = new JPH::Factory();
    JPH::RegisterTypes();

    temp_allocator = new JPH::TempAllocatorImpl(10 * 1024 * 1024);
    job_system = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, static_cast<int>(std::thread::hardware_concurrency()) - 1);

    const JPH::uint cMaxBodies = 1024;
    const JPH::uint cNumBodyMutexes = 0;
    const JPH::uint cMaxBodyPairs = 1024;
    const JPH::uint cMaxContactConstraints = 1024;

    broad_phase_layer_interface = new JPH::BPLayerInterfaceImpl();
    object_vs_broadphase_layer_filter = new JPH::ObjectVsBroadPhaseLayerFilterImpl();
    object_vs_object_layer_filter = new JPH::ObjectLayerPairFilterImpl();

    physics_system = new JPH::PhysicsSystem();
    physics_system->Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, *broad_phase_layer_interface, *object_vs_broadphase_layer_filter, *object_vs_object_layer_filter);

    physics_system->SetBodyActivationListener(body_activation_listener);
    physics_system->SetContactListener(contact_listener);

    floor_shape_settings = new JPH::BoxShapeSettings(JPH::Vec3(100.0f, 1.0f, 100.0f));
    floor_shape_settings->SetEmbedded();


    floor_shape_result = floor_shape_settings->Create();
    floor_shape = floor_shape_result.Get();

    floor_settings = new JPH::BodyCreationSettings(floor_shape, JPH::RVec3(0.0f, -1.0f, 0.0f), JPH::Quat::sIdentity(), JPH::EMotionType::Static, JPH::Layers::NON_MOVING);

    floor = GetBodyInterface().CreateBody(*floor_settings);


    GetBodyInterface().AddBody(floor->GetID(), JPH::EActivation::DontActivate);

    sphere_settings = new JPH::BodyCreationSettings(new JPH::SphereShape(0.5f), JPH::RVec3(0.0f, 2.0f, 0.0f), JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, JPH::Layers::MOVING);
    sphere_id = GetBodyInterface().CreateAndAddBody(*sphere_settings, JPH::EActivation::Activate);

    GetBodyInterface().SetLinearVelocity(sphere_id, JPH::Vec3(0.0f, -5.0f, 0.0f));

    cDeltaTime = 1.0f / 60.0f;

    physics_system->OptimizeBroadPhase();
    step = 0;
}

void Physics::Update_JOLT()
{
    if (!GetBodyInterface().IsActive(sphere_id))
        return;

    ++step;

    JPH::RVec3 position = GetBodyInterface().GetCenterOfMassPosition(sphere_id);
    JPH::Vec3 velocity = GetBodyInterface().GetLinearVelocity(sphere_id);
    std::cout << "Step " << step << ": Position = (" << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << "), Velocity = (" << velocity.GetX() << ", " << velocity.GetY() << ", " << velocity.GetZ() << ")" << std::endl;

    const int cCollisionSteps = 1;
    // Step the world
    physics_system->Update(cDeltaTime, cCollisionSteps, temp_allocator, job_system);
}


void Physics::Clean_JOLT()
{
    GetBodyInterface().RemoveBody(sphere_id);
    GetBodyInterface().DestroyBody(sphere_id);

    GetBodyInterface().RemoveBody(floor->GetID());
    GetBodyInterface().DestroyBody(floor->GetID());

    JPH::UnregisterTypes();

    delete JPH::Factory::sInstance;
    JPH::Factory::sInstance = nullptr;
}

JPH::Body* Physics::CreateBody() { return nullptr; }

JPH::BodyInterface& Physics::GetBodyInterface() const { return physics_system->GetBodyInterface(); }

