#pragma once

#include "LayerSystem.hpp"

#include "jolt/Jolt/Jolt.h"
#include "jolt/Jolt/Physics/PhysicsSystem.h"
#include "Logger.hpp"


// TODO : Finish this class
class PhysicsCollisionListener final : public JPH::ContactListener
{
public:
    explicit PhysicsCollisionListener() = default;

    inline void OnContactAdded(const JPH::Body& a_inBody1, const JPH::Body& a_inBody2, const JPH::ContactManifold& a_inManifold, JPH::ContactSettings& a_ioSettings) override
    {

        DEBUG_LOG_INFO("bite");
        static_cast<void>(a_inManifold); static_cast<void>(a_ioSettings);
        if (a_inBody1.IsSensor() || a_inBody2.IsSensor())
        {
            
        }
    }


    inline void OnContactRemoved(const JPH::SubShapeIDPair& a_inSubShapePair) override
    {
        static_cast<void>(a_inSubShapePair);
        //JPH::BodyID l_body1 = a_inSubShapePair.GetBody1ID();
        //JPH::BodyID l_body2 = a_inSubShapePair.GetBody2ID();

        // Notify collision exit
    }


    inline void OnContactPersisted(const JPH::Body& a_inBody1, const JPH::Body& a_inBody2, const JPH::ContactManifold& a_inManifold, JPH::ContactSettings& a_ioSettings) override
    {
        static_cast<void>(a_inManifold); static_cast<void>(a_ioSettings);
        if (a_inBody1.IsSensor() || a_inBody2.IsSensor())
        {
            // Notify collision says between both bodies
        }
    }


    inline JPH::ValidateResult OnContactValidate(const JPH::Body& a_inBody1, const JPH::Body& a_inBody2, JPH::RVec3Arg a_inBaseOffset, const JPH::CollideShapeResult& a_inCollisionResult) override
    {
        static_cast<void>(a_inBaseOffset); static_cast<void>(a_inCollisionResult);
        if (a_inBody1.GetObjectLayer() == Layers::DISABLED || a_inBody2.GetObjectLayer() == Layers::DISABLED)
            return JPH::ValidateResult::RejectContact;

        return JPH::ValidateResult::AcceptContact;
    }
};