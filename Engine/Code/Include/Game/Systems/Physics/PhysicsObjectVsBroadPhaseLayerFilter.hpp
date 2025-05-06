#pragma once

#include "Game/Systems/Physics/LayerSystem.hpp"
#include "jolt/Jolt/Jolt.h"
#include "jolt/Jolt/Physics/PhysicsSystem.h"


class PhysicsObjectVsBroadPhaseLayerFilter final : public JPH::ObjectVsBroadPhaseLayerFilter
{
public:
    inline bool ShouldCollide(const JPH::ObjectLayer a_inLayer1, const JPH::BroadPhaseLayer a_inLayer2) const override
    {
        switch (a_inLayer1)
        {
            case Layers::STATIC:
                return a_inLayer2 == BroadPhaseLayers::DYNAMIC;
            case Layers::DYNAMIC:
            case Layers::SENSOR:
                return true;
            case Layers::DISABLED:
                return false;
            default:
                JPH_ASSERT(false);
                return false;
        }
    };
};