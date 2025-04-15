#pragma once

#include "Jolt/Core/Core.h"
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

    JPH::uint step { 0.f; }
    float cDeltaTime{ 0.f };
    JPH::PhysicsSystem* physics_system{ nullptr };
    BodyID sphere_id{ };

    JPH::BPLayerInterfaceImpl* broad_phase_layer_interface{ nullptr };
    JPH::ObjectVsBroadPhaseLayerFilterImpl* object_vs_broadphase_layer_filter{ nullptr };
    JPH::ObjectLayerPairFilterImpl* object_vs_object_layer_filter{ nullptr };

    JPH::TempAllocatorImpl* temp_allocator{ nullptr };
    JPH::JobSystemThreadPool* job_system{ nullptr };
};


