#include "Game/Systems/Physics/Layers.hpp"

JPH_NAMESPACE_BEGIN

bool ObjectLayerPairFilterImpl::ShouldCollide(const ObjectLayer a_inObject1, const ObjectLayer a_inObject2) const
{
    switch (a_inObject1)
    {
        case Layers::NON_MOVING:
            return a_inObject2 == Layers::MOVING;
        case Layers::MOVING:
            return true;
        default:
            JPH_ASSERT(false);
            return false;
    }
}

uint BPLayerInterfaceImpl::GetNumBroadPhaseLayers() const 
{
    return BroadPhaseLayers::NUM_LAYERS;
}

BroadPhaseLayer BPLayerInterfaceImpl::GetBroadPhaseLayer(const ObjectLayer a_inLayer) const
{
    JPH_ASSERT(a_inLayer < Layers::NUM_LAYERS);
    return mObjectToBroadPhase[a_inLayer];
}



bool ObjectVsBroadPhaseLayerFilterImpl::ShouldCollide(const ObjectLayer a_inLayer1, const BroadPhaseLayer a_inLayer2) const
{
    switch (a_inLayer1)
    {
        case Layers::NON_MOVING:
            return a_inLayer2 == BroadPhaseLayers::MOVING;
        case Layers::MOVING:
            return true;
        default:
            JPH_ASSERT(false);
            return false;
    }
}

JPH_NAMESPACE_END
