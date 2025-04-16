#pragma once

#include "Jolt/Jolt.h"
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


class Physics
{
public:
    Physics() = default;
    ~Physics() = default;

    void Init_JOLT();
    void Update_JOLT();
    void Clean_JOLT();

    JPH::Body* CreateBody();

private:
    [[nodiscard]] JPH::BodyInterface& GetBodyInterface() const;

    float cDeltaTime{ 0.f };
    JPH::uint step { 0 };
    JPH::PhysicsSystem* physics_system{ nullptr };
    JPH::BodyID sphere_id{ };
    JPH::Body* floor{ nullptr };

    JPH::BPLayerInterfaceImpl* broad_phase_layer_interface{ nullptr };
    JPH::ObjectVsBroadPhaseLayerFilterImpl* object_vs_broadphase_layer_filter{ nullptr };
    JPH::ObjectLayerPairFilterImpl* object_vs_object_layer_filter{ nullptr };

    JPH::TempAllocatorImpl* temp_allocator{ nullptr };
    JPH::JobSystemThreadPool* job_system{ nullptr };

    JPH::MyBodyActivationListener* body_activation_listener{ nullptr };
    JPH::MyContactListener* contact_listener{ nullptr };
    JPH::BoxShapeSettings* floor_shape_settings { nullptr };
    JPH::ShapeSettings::ShapeResult floor_shape_result;
    JPH::ShapeRefC floor_shape;

    JPH::BodyCreationSettings* floor_settings{ nullptr };
    JPH::BodyCreationSettings* sphere_settings{ nullptr };
};


