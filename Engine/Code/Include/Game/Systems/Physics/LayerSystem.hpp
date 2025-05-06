#pragma once

#include "jolt/Jolt/Jolt.h"
#include "jolt/Jolt/Physics/PhysicsSystem.h"
#include "jolt/Jolt/Physics/Body/BodyCreationSettings.h"


namespace Layers
{
    static constexpr JPH::ObjectLayer DISABLED = 0; // Does not collide at all
    static constexpr JPH::ObjectLayer STATIC = 1; // Collides with Dynamic and Kinematic objects
    static constexpr JPH::ObjectLayer DYNAMIC = 2; // Collides with everything
    static constexpr JPH::ObjectLayer SENSOR = 3 ;
    static constexpr JPH::ObjectLayer KINEMATIC = 4 ;
    static constexpr JPH::ObjectLayer NUM_LAYERS = 5;
};


namespace BroadPhaseLayers
{
    static constexpr JPH::BroadPhaseLayer DISABLED(0);
    static constexpr JPH::BroadPhaseLayer STATIC(1);
    static constexpr JPH::BroadPhaseLayer DYNAMIC(2);
    static constexpr JPH::BroadPhaseLayer SENSOR(3);
    static constexpr JPH::BroadPhaseLayer KINEMATIC(4);
    static constexpr JPH::uint NUM_LAYERS(5);
};