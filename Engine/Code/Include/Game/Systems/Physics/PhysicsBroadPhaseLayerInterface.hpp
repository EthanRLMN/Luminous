#pragma once
#include "jolt/Jolt/Jolt.h"
#include "jolt/Jolt/Physics/PhysicsSystem.h"

#include "Game/Systems/Physics/LayerSystem.hpp"


class PhysicsBroadPhaseLayerInterface final : public JPH::BroadPhaseLayerInterface
{
public:
    explicit PhysicsBroadPhaseLayerInterface()
    {
        m_objectToBroadPhase[Layers::DISABLED] = BroadPhaseLayers::DISABLED;
        m_objectToBroadPhase[Layers::STATIC] = BroadPhaseLayers::STATIC;
        m_objectToBroadPhase[Layers::DYNAMIC] = BroadPhaseLayers::DYNAMIC;
        m_objectToBroadPhase[Layers::SENSOR] = BroadPhaseLayers::SENSOR;
    }

    [[nodiscard]] inline JPH::uint GetNumBroadPhaseLayers() const override { return BroadPhaseLayers::NUM_LAYERS; }
    [[nodiscard]] inline JPH::BroadPhaseLayer GetBroadPhaseLayer(const JPH::ObjectLayer a_inLayer) const override
    {
        JPH_ASSERT(a_inLayer < Layers::NUM_LAYERS);
        return m_objectToBroadPhase[a_inLayer];
    }


private:
    JPH::BroadPhaseLayer m_objectToBroadPhase[Layers::NUM_LAYERS]{};
};