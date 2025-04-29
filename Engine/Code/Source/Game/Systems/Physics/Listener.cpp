#include "Game/Systems/Physics/Listener.hpp"

JPH_NAMESPACE_BEGIN

ValidateResult MyContactListener::OnContactValidate(const Body& inBody1, const Body& inBody2, RVec3Arg inBaseOffset, const CollideShapeResult& inCollisionResult)
{
    std::cout << "Contact validate callback" << std::endl;

    return ValidateResult::AcceptAllContactsForThisBodyPair;
}

void MyContactListener::OnContactAdded(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings)
{
    std::cout << "A contact was added" << std::endl;
}

void MyContactListener::OnContactPersisted(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings)
{
    std::cout << "A contact was persisted" << std::endl;
}

void MyContactListener::OnContactRemoved(const SubShapeIDPair& inSubShapePair) 
{
    std::cout << "A contact was removed" << std::endl;
}


void MyBodyActivationListener::OnBodyActivated(const BodyID& inBodyID, uint64 inBodyUserData) 
{
    std::cout << "A body got activated" << std::endl;
}

void MyBodyActivationListener::OnBodyDeactivated(const BodyID& inBodyID, uint64 inBodyUserData) 
{
    std::cout << "A body went to sleep" << std::endl;
}

JPH_NAMESPACE_END