#include "Game/Systems/Physics/PhysicsSystem.hpp"

#include <thread>
#include <ranges>
#include "Jolt/RegisterTypes.h"
#include "Jolt/Core/Factory.h"
#include "Jolt/Core/JobSystemThreadPool.h"
#include "Jolt/Core/Memory.h"
#include "Jolt/Physics/PhysicsSettings.h"


#include "Game/Systems/Time.inl"
#include "Game/Systems/Component/RigidbodyComponent.hpp"
#include "Game/Systems/Entity/Entity.hpp"
#include "Game/Systems/Physics/BodyActivationListener.hpp"
#include "Game/Systems/Physics/PhysicsBroadPhaseLayerInterface.hpp"
#include "Game/Systems/Physics/PhysicsCollisionListener.hpp"
#include "Game/Systems/Physics/PhysicsObjectLayerPairFilter.hpp"
#include "Game/Systems/Physics/PhysicsObjectVsBroadPhaseLayerFilter.hpp"

#include "jolt/Physics/Body/Body.h"


// Default value for the TempAllocator (10MB by default)
constexpr JPH::uint32 TempAllocatorSize = 10 * 1024 * 1024;


void PhysicsSystem::Init(const Settings& a_settings)
{
    JPH::RegisterDefaultAllocator(); // Register the memory allocator (Default is malloc)

    JPH::Factory::sInstance = new JPH::Factory(); // Set up the factory used for creating instances of classes based on their names
    JPH::RegisterTypes(); // Register all physics types with the factory and install their collision handlers with the CollisionDispatch class

    m_tempAllocator = new JPH::TempAllocatorImpl(TempAllocatorSize); // Set up the temporary allocator size
    m_jobSystem = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, static_cast<int>(std::thread::hardware_concurrency()) - 1); // Init the job system to execute physics on multiple threads

    m_broadPhaseLayerInterface = new PhysicsBroadPhaseLayerInterface(); // Create a mapping table from object layer to broad phase layer
    m_ObjToBroadPhaseLayerFilter = new PhysicsObjectVsBroadPhaseLayerFilter(); // Create a class that filters object vs. broad phase layers
    m_ObjToObjLayerFilter = new PhysicsObjectLayerPairFilter(); // Create a class that filters object vs. object layers

    m_physicsSystem = new JPH::PhysicsSystem(); // Create the physics system and initialize it with all the previous data
    m_physicsSystem->Init(a_settings.m_maxRigidBodies, a_settings.m_bodyMutexNumber, a_settings.m_maxBodyPairs, a_settings.m_maxContactConstraints, *m_broadPhaseLayerInterface, *m_ObjToBroadPhaseLayerFilter, *m_ObjToObjLayerFilter);

    m_bodyActivationListener = new PhysicsBodyActivationListener(); // Create a body activation listener that gets notified when bodies activate and go to sleep | MUST BE THREAD SAFE
    m_physicsSystem->SetBodyActivationListener(m_bodyActivationListener);

    m_collisionListener = new PhysicsCollisionListener(this); // Create a contact listener that gets notified when bodies (are about to) collide, and when they separate again | MUST BE THREAD SAFE
    
    m_physicsSystem->SetContactListener(m_collisionListener);

    
    

    /*
    JPH::BoxShapeSettings settings(JPH::Vec3(40.0f, 50.f, 50.f));
    settings.SetEmbedded();
    JPH::ShapeSettings::ShapeResult floor_shape_result = settings.Create();
    JPH::ShapeRefC floor_shape = floor_shape_result.Get();
    l_rigidbodySource = CreateRigidBody(floor_shape);
    l_rigidbodySource->SetIsSensor(true);

    l_rigidbodySource->AddForce(JPH::Vec3Arg(-5.0f, 0.0f, 0.0f));

    JPH::BoxShapeSettings settings2(JPH::Vec3(50.f, 50.f, 50.f));
    settings2.SetEmbedded();
    JPH::ShapeSettings::ShapeResult floor_shape_result2 = settings2.Create();
    JPH::ShapeRefC floor_shape2 = floor_shape_result2.Get();

    
    
    l_rigidbodySource2 = CreateRigidBody(floor_shape2);
    l_rigidbodySource2->SetIsSensor(true);
    l_rigidbodySource2->AddForce(JPH::Vec3Arg(0.0f, 5.0f, 0.0f));*/
    //DEBUG_LOG_INFO("{}", GetBodyInterface().);
    
    
}


void PhysicsSystem::Update()
{
    for (const RigidBody* l_rigidBody : m_rigidBodies)
        if (!GetBodyInterface().IsActive(l_rigidBody->GetRigidBodyID()))
            return;

    // TODO : Update collision steps to run properly (accumulator returns floats on a scale from 0.25 to 10, we need integers scaled properly)
    constexpr int l_step { 1 };
    
    
    
        

    m_physicsSystem->Update(Time::GetFixedDeltaTime(), l_step, m_tempAllocator, m_jobSystem);

    for (RigidBody* const& l_resource : m_bodiesToRigidBodies | std::views::values)
    {
        l_resource->UpdateToTransform();
    }
}


void PhysicsSystem::Destroy()
{
    for (const RigidBody* l_rigidBody : m_rigidBodies)
    {
        GetBodyInterface().RemoveBody(l_rigidBody->GetRigidBodyID());
        GetBodyInterface().DestroyBody(l_rigidBody->GetRigidBodyID());
    }

    delete m_collisionListener;
    m_collisionListener = nullptr;

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


RigidBody* PhysicsSystem::CreateRigidBody(const JPH::Shape* a_shape, JPH::Vec3 a_pos, JPH::Quat a_rot, JPH::uint8 a_layer, JPH::EActivation a_activate)
{
    JPH::EMotionType l_motionType = JPH::EMotionType::Static;
    if (a_layer == Layers::DYNAMIC)
        l_motionType = JPH::EMotionType::Dynamic;
    else if (a_layer == Layers::KINEMATIC)
        l_motionType = JPH::EMotionType::Kinematic;
    else l_motionType = JPH::EMotionType::Static;

    // Body settings
    JPH::BodyCreationSettings l_bodySettings(
        a_shape,
        a_pos,
        a_rot,
        l_motionType,
        a_layer
    );
    if (a_layer == Layers::DYNAMIC)
        l_bodySettings.mAllowSleeping = false;

    if (a_layer == Layers::SENSOR)
        l_bodySettings.mIsSensor = true;

    // Set up the gravity factor
    l_bodySettings.mGravityFactor = Settings().m_gravityFactor;

    JPH::Body* l_body = GetBodyInterface().CreateBody(l_bodySettings);
    GetBodyInterface().AddBody(l_body->GetID(), a_activate);
    
    RigidBody* l_rig = new RigidBody(l_body);

    //m_rigidBodies.emplace_back(l_rig);

    JPH::Quat quat = l_body->GetRotation();

    m_bodiesToRigidBodies[l_body->GetID()] = l_rig;

    return l_rig;
}


RigidBody* PhysicsSystem::CreateBox(const Maths::Vector3 a_scale)
{
    const JPH::Vec3 l_halfSize = JPH::Vec3(a_scale.x * 0.5f, a_scale.y * 0.5f,a_scale.z * 0.5f);
    return CreateRigidBody(new JPH::BoxShape(l_halfSize));
}


void PhysicsSystem::RemoveBody(const JPH::BodyID& a_bodyId)
{
    GetBodyInterface().RemoveBody(a_bodyId);

    std::erase_if(m_rigidBodies, [&a_bodyId](const RigidBody* a_rigidBody) { return a_bodyId == a_rigidBody->GetRigidBodyID(); });
}


void PhysicsSystem::RemoveAllBodies()
{
    for (const RigidBody* l_body : m_rigidBodies)
        RemoveBody(l_body->GetRigidBodyID());

    m_rigidBodies.clear();
}


