#include "Game/Systems/Physics/CollisionSystem.hpp"

#include <iostream>


JPH::ValidateResult PhysicsContactListener::OnContactValidate(const JPH::Body& inBody1, const JPH::Body& inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult& inCollisionResult)
{
    std::cout << "Contact validate callback" << std::endl;

    return JPH::ValidateResult::AcceptAllContactsForThisBodyPair;
}

void PhysicsContactListener::OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
{
    std::cout << "A contact was added" << std::endl;
}

void PhysicsContactListener::OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
{
    std::cout << "A contact was persisted" << std::endl;
}

void PhysicsContactListener::OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair)
{
    std::cout << "A contact was removed" << std::endl;
}


void PhysicsBodyActivationListener::OnBodyActivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData)
{
    std::cout << "A body got activated" << std::endl;
}

void PhysicsBodyActivationListener::OnBodyDeactivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData)
{
    std::cout << "A body went to sleep" << std::endl;
}