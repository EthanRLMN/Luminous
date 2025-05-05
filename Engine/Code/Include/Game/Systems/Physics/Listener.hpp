#pragma once

#include <cstdarg>
#include <iostream>
#include <thread>

#include "Struct/Vertex.hpp"

#include "jolt/Jolt/Jolt.h"
#include "jolt/Jolt/Physics/PhysicsSystem.h"
#include "jolt/Jolt/Physics/Body/BodyActivationListener.h"
#include "jolt/Physics/PhysicsScene.h"


class PhysicsContactListener final : public JPH::ContactListener
{
public:
    virtual JPH::ValidateResult OnContactValidate(const JPH::Body& inBody1, const JPH::Body& inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult& inCollisionResult) override;


    virtual void OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override;

    virtual void OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override;


    virtual void OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair) override;
};


class PhysicsBodyActivationListener final : public JPH::BodyActivationListener
{
public:
    virtual void OnBodyActivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override;

    virtual void OnBodyDeactivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override;

};