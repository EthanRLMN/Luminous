#pragma once

#include <iostream>
#include <thread>
#include "Logger.hpp"

#include "jolt/Jolt/Jolt.h"
#include "jolt/Jolt/Physics/PhysicsSystem.h"
#include "jolt/Jolt/Physics/Body/BodyCreationSettings.h"

JPH_NAMESPACE_BEGIN

namespace Layers
{
    static constexpr ObjectLayer NON_MOVING = 0;
    static constexpr ObjectLayer MOVING = 1;
    static constexpr ObjectLayer NUM_LAYERS = 2;
}; 

class ObjectLayerPairFilterImpl : public ObjectLayerPairFilter
{
public:
    bool ShouldCollide(ObjectLayer a_inObject1, ObjectLayer a_inObject2) const override;
};

namespace BroadPhaseLayers
{
    static constexpr BroadPhaseLayer NON_MOVING(0);
    static constexpr BroadPhaseLayer MOVING(1);
    static constexpr uint NUM_LAYERS(2);
}; 

class BPLayerInterfaceImpl final : public BroadPhaseLayerInterface
{
public:
    BPLayerInterfaceImpl()
    {
        mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
        mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
    }

    uint GetNumBroadPhaseLayers() const override;
    BroadPhaseLayer GetBroadPhaseLayer(ObjectLayer a_inLayer) const override;


private:
    BroadPhaseLayer mObjectToBroadPhase[Layers::NUM_LAYERS];
};


class ObjectVsBroadPhaseLayerFilterImpl : public ObjectVsBroadPhaseLayerFilter
{
public:
    bool ShouldCollide(ObjectLayer a_inLayer1, BroadPhaseLayer a_inLayer2) const override;
};


JPH_NAMESPACE_END
