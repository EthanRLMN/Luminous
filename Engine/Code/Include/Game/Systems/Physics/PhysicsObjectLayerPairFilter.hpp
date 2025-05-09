#pragma once

#include "Game/Systems/Physics/LayerSystem.hpp"
#include "jolt/Jolt/Jolt.h"


class PhysicsObjectLayerPairFilter final : public JPH::ObjectLayerPairFilter
{
public:
    [[nodiscard]] inline bool ShouldCollide(const JPH::ObjectLayer a_inObject1, const JPH::ObjectLayer a_inObject2) const override
    {
        switch (a_inObject1)
        {
            case Layers::STATIC: // Only trigger collisions with DYNAMIC objects
                return a_inObject2 == Layers::DYNAMIC;
            case Layers::DYNAMIC: // Collides with everything
            case Layers::SENSOR:
                return true;
            case Layers::DISABLED: // Disable all collisions
                return false;
            default:
                JPH_ASSERT(false);
                return false;
        }
    }
};